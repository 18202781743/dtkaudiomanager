// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "daudiomanager_daemon.h"
#include "daudiocard_daemon.h"
#include "daudioport_daemon.h"
#include "daudiodevice_daemon.h"
#include "daudiocard.h"
#include "daudiodevice.h"
#include "daudiostream_daemon.h"
#include "daemonhelpers.hpp"

#include <QDBusAbstractInterface>
#include <QDBusReply>
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

DAUDIOMANAGER_BEGIN_NAMESPACE

DDaemonAudioManager::DDaemonAudioManager(QObject *parent)
{
    m_inter = new DDBusInterface(DDaemonInternal::AudioServiceName, DDaemonInternal::AudioPath);
    if (!m_inter->isValid()) {
        qWarning() << m_inter->lastError();
    }

    updateCards();
}

DDaemonAudioManager::~DDaemonAudioManager()
{

}

void DDaemonAudioManager::reset()
{
    m_inter->call("reset");
}

void DDaemonAudioManager::setReConnectionEnabled(const bool enable)
{

}

void DDaemonAudioManager::setPort(const QString &card, const QString &portName, const int direction)
{

}

void DDaemonAudioManager::setPortEnabled(const QString &card, const QString &portName)
{

}

bool DDaemonAudioManager::increaseVolume() const
{
    return false;
}

bool DDaemonAudioManager::reduceNoise() const
{
    return false;
}

bool DDaemonAudioManager::maxVolume() const
{
    return false;
}

void DDaemonAudioManager::setIncreaseVolume(bool increaseVolume)
{

}

void DDaemonAudioManager::setReduceNoise(bool reduceNoise)
{

}

void DDaemonAudioManager::updateCards()
{
    const QDBusReply<QString> &reply = m_inter->call("cards");
    if (!reply.isValid()) {
        qWarning() << Q_FUNC_INFO << reply.error();
        return;
    }
    QJsonDocument doc = QJsonDocument::fromJson(reply.value().toUtf8());
    QJsonArray jCards = doc.array();
    for (QJsonValue cV : jCards) {
        QJsonObject jCard = cV.toObject();
        const uint cardId = static_cast<uint>(jCard["Id"].toInt());
        const QString cardName = jCard["Name"].toString();
        QJsonArray jPorts = jCard["Ports"].toArray();

        auto card = new DDaemonAudioCard();
        m_cards << card;
        card->m_name = cardName;

        for (QJsonValue pV : jPorts) {
            QJsonObject jPort = pV.toObject();
            const double portAvai = jPort["Available"].toDouble();
            const bool aviablee = (portAvai == 2.0 || portAvai == 0.0);// 0 Unknown 1 Not available 2 Available
            const QString portId = jPort["Name"].toString();
            const QString portName = jPort["Description"].toString();
            const bool isEnabled = jPort["Enabled"].toBool();
            const bool isBluetooth = jPort["Bluetooth"].toBool();
            const int direction = jPort["Direction"].toInt();

            auto port = new DDaemonAudioPort(card);
            port->setEnabled(isEnabled);
        }
    }
}

void DDaemonAudioManager::updateInputDevice()
{
    const QDBusReply<QString> &reply = m_inter->call("sources");
    if (!reply.isValid()) {
        qWarning() << Q_FUNC_INFO << reply.error();
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(reply.value().toUtf8());
    QJsonArray root = doc.array();
    for (auto item : root) {
        const auto &path = item.toString();

        DPlatformAudioCard *card = nullptr;
        DDBusInterface inter(DDaemonInternal::AudioServiceName, path);
        const auto cardId = qdbus_cast<quint32>(inter.property("card"));
        for (auto item : m_cards) {
            if (item->index() == cardId) {
                card = item;
                break;
            }
        }
        auto device = new DDaemonAudioInputDevice(path, card);
        m_inputDevices << device;
    }
}

void DDaemonAudioManager::updateOutputDevice()
{
    const QDBusReply<QString> &reply = m_inter->call("sinks");
    if (!reply.isValid()) {
        qWarning() << Q_FUNC_INFO << reply.error();
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(reply.value().toUtf8());
    QJsonArray root = doc.array();
    for (auto item : root) {
        const auto &path = item.toString();

        DPlatformAudioCard *card = nullptr;
        DDBusInterface inter(DDaemonInternal::AudioServiceName, path);
        const auto cardId = qdbus_cast<quint32>(inter.property("card"));
        for (auto item : m_cards) {
            if (item->index() == cardId) {
                card = item;
                break;
            }
        }
        auto device = new DDaemonAudioOutputDevice(path, card);
        m_outputDevices << device;
    }
}

void DDaemonAudioManager::updateOutputStream()
{
    const QDBusReply<QString> &reply = m_inter->call("sourceoutput");
    if (!reply.isValid()) {
        qWarning() << Q_FUNC_INFO << reply.error();
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(reply.value().toUtf8());
    QJsonArray root = doc.array();
    for (auto item : root) {
        const auto &path = item.toString();

        DPlatformAudioInputDevice *device = nullptr;
        DDBusInterface inter(DDaemonInternal::AudioServiceName, path);
        const auto sinkIndex = qdbus_cast<quint32>(inter.property("sinkIndex"));
        for (auto item : m_inputDevices) {
            if (item->key() == QString::number(sinkIndex)) {
                device = item;
                break;
            }
        }
        auto stream = new DDaemonOutputStream(path, device);
        m_outputStreams << stream;
    }
}

void DDaemonAudioManager::updateInputStream()
{
    const QDBusReply<QString> &reply = m_inter->call("sinkinput");
    if (!reply.isValid()) {
        qWarning() << Q_FUNC_INFO << reply.error();
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(reply.value().toUtf8());
    QJsonArray root = doc.array();
    for (auto item : root) {
        const auto &path = item.toString();

        DPlatformAudioOutputDevice *device = nullptr;
        DDBusInterface inter(DDaemonInternal::AudioServiceName, path);
        const auto sinkIndex = qdbus_cast<quint32>(inter.property("sinkIndex"));
        for (auto item : m_outputDevices) {
            if (item->key() == QString::number(sinkIndex)) {
                device = item;
                break;
            }
        }
        auto stream = new DDaemonInputStream(path, device);
        m_inputStreams << stream;
    }
}

DAUDIOMANAGER_END_NAMESPACE
