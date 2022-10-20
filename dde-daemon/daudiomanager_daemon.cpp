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
    m_inter = DDaemonInternal::newAudioInterface();
//    m_inter->setTimeout(300);
    if (!m_inter->isValid()) {
        qWarning() << m_inter->lastError();
    }

    updateCards();

    updateOutputDevice();
    updateInputStream();

    updateInputDevice();
    updateOutputStream();
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
    return qdbus_cast<bool>(m_inter->property("increaseVolume"));
}

bool DDaemonAudioManager::reduceNoise() const
{
    return qdbus_cast<bool>(m_inter->property("reduceNoise"));
}

double DDaemonAudioManager::maxVolume() const
{
    return qdbus_cast<double>(m_inter->property("maxVolume"));
}

void DDaemonAudioManager::setIncreaseVolume(bool increaseVolume)
{

}

void DDaemonAudioManager::setReduceNoise(bool reduceNoise)
{

}

void DDaemonAudioManager::updateCards()
{
    const QString &replyValue = qdbus_cast<QString>(m_inter->property("Cards"));
    if (m_inter->lastError().isValid()) {
        qWarning() << Q_FUNC_INFO << m_inter->lastError();
        return;
    }
    QJsonDocument doc = QJsonDocument::fromJson(replyValue.toUtf8());
    QJsonArray jCards = doc.array();
    for (QJsonValue cV : jCards) {
        QJsonObject jCard = cV.toObject();
        const uint cardId = static_cast<uint>(jCard["Id"].toInt());
        const QString cardName = jCard["Name"].toString();
        QJsonArray jPorts = jCard["Ports"].toArray();

        auto card = new DDaemonAudioCard();
        card->m_name = cardName;

        for (QJsonValue pV : jPorts) {
            QJsonObject jPort = pV.toObject();
            const double portAvai = jPort["Available"].toDouble();
            const bool aviablee = (portAvai == 2.0 || portAvai == 0.0);// 0 Unknown 1 Not available 2 Available
            const QString portName = jPort["Name"].toString();
            const QString portDescription = jPort["Description"].toString();
            const bool isEnabled = jPort["Enabled"].toBool();
            const bool isBluetooth = jPort["Bluetooth"].toBool();
            const int direction = jPort["Direction"].toInt();

            auto port = new DDaemonAudioPort(card);
            port->setEnabled(isEnabled);
            port->m_name = portName;
            port->m_description = portDescription;
        }
        addCard(card);
    }
}

void DDaemonAudioManager::updateInputDevice()
{
    auto sinkPaths = qdbus_cast<QList<QDBusObjectPath>>(m_inter->property("Sources"));
    if (m_inter->lastError().isValid()) {
        qWarning() << Q_FUNC_INFO << m_inter->lastError();
        return;
    }

    for (auto item : sinkPaths) {
        const auto &path = item.path();
        const auto &deviceName = DDaemonInternal::deviceName(path);
        if (containInputDevice(deviceName))
            continue;

        DPlatformAudioCard *card = nullptr;
        auto inter = DDaemonInternal::audioInterface(path);
        const auto cardId = qdbus_cast<quint32>(inter.property("Card"));
        for (auto item : m_cards) {
            if (item->index() == cardId) {
                card = item.data();
                break;
            }
        }
        if (!card) {
            qWarning() << "Don't find card for the inputDevice" << path;
            return;
        }
        auto device = new DDaemonAudioInputDevice(path, card);
        device->setName(deviceName);

        m_inputDevices << device;
    }
}

void DDaemonAudioManager::updateOutputDevice()
{
    auto sinkPaths = qdbus_cast<QList<QDBusObjectPath>>(m_inter->property("Sinks"));
    if (m_inter->lastError().isValid()) {
        qWarning() << Q_FUNC_INFO << m_inter->lastError();
        return;
    }

    for (auto item : sinkPaths) {
        const auto &path = item.path();
        const auto &deviceName = DDaemonInternal::deviceName(path);
        if (containOutputDevice(deviceName))
            continue;

        DPlatformAudioCard *card = nullptr;
        auto inter = DDaemonInternal::audioInterface(path);
        const auto cardId = qdbus_cast<quint32>(inter.property("Card"));
        for (auto item : m_cards) {
            if (item->index() == cardId) {
                card = item.data();
                break;
            }
        }
        auto device = new DDaemonAudioOutputDevice(path, card);
        device->setName(deviceName);

        m_outputDevices << device;
    }
}

void DDaemonAudioManager::updateOutputStream()
{
    auto sourceOutputPaths = qdbus_cast<QList<QDBusObjectPath>>(m_inter->property("SourceOutputs"));
    if (m_inter->lastError().isValid()) {
        qWarning() << Q_FUNC_INFO << m_inter->lastError();
        return;
    }

    for (auto item : sourceOutputPaths) {
        const auto &path = item.path();
        const auto streamName = DDaemonInternal::streamName(path);

        DPlatformAudioInputDevice *device = nullptr;
        auto inter = DDaemonInternal::audioInterface(path);
        const auto sinkIndex = qdbus_cast<quint32>(inter.property("SinkIndex"));
        for (auto item : m_inputDevices) {
            if (item->key() == QString::number(sinkIndex)) {
                device = item;
                break;
            }
        }
        if (!device) {
            qWarning() << "Don't find inputDevice for the outputStream" << path;
            return;
        }
        auto stream = new DDaemonOutputStream(path, device);
        stream->setName(streamName);
        device->addStream(stream);
    }
}

void DDaemonAudioManager::updateInputStream()
{
    auto sinkInputPaths = qdbus_cast<QList<QDBusObjectPath>>(m_inter->property("SinkInputs"));
    if (m_inter->lastError().isValid()) {
        qWarning() << Q_FUNC_INFO << m_inter->lastError();
        return;
    }

    for (auto item : sinkInputPaths) {
        const auto &path = item.path();
        const auto streamName = DDaemonInternal::streamName(path);

        DPlatformAudioOutputDevice *device = nullptr;
        auto inter = DDaemonInternal::audioInterface(path, DDaemonInternal::AudioServiceSinkInputInterface);
        const auto sinkIndex = qdbus_cast<quint32>(inter.property("SinkIndex"));
        for (auto item : m_outputDevices) {
            if (item->name() == QString::number(sinkIndex)) {
                device = item;
                break;
            }
        }
        if (!device) {
            qWarning() << "Don't find outputDevice for the inputStream" << path;
            return;
        }
        auto stream = new DDaemonInputStream(path, device);
        stream->setName(streamName);
        device->addStream(stream);
    }
}

bool DDaemonAudioManager::containInputDevice(const QString &deviceName)
{
    for (auto item : m_inputDevices) {
        if (item->name() == deviceName)
            return true;
    }
    return false;
}

bool DDaemonAudioManager::containOutputDevice(const QString &deviceName)
{
    for (auto item : m_outputDevices) {
        if (item->name() == deviceName)
            return true;
    }
    return false;
}

DAUDIOMANAGER_END_NAMESPACE
