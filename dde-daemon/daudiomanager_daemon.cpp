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
    : m_inter(DDaemonInternal::newAudioInterface2(this))
{
//    m_inter->setTimeout(300);
    if (!m_inter->isValid()) {
        qWarning() << m_inter->lastError();
    }

    updateCards();

    updateOutputDevice();
    updateInputStream();

    updateInputDevice();
    updateOutputStream();

    connect(this, &DDaemonAudioManager::CardsChanged, this, [this](const QString &cards) {
        Q_UNUSED(cards);
        updateCards();
    });
    connect(this, &DDaemonAudioManager::CardsWithoutUnavailableChanged, this, [this](const QString &availableCards) {
        Q_UNUSED(availableCards);
        updateCards();
    });
    connect(this, &DDaemonAudioManager::SinkInputsChanged, this, [this](const QList<QDBusObjectPath> &paths) {
        Q_UNUSED(paths);
        updateInputStream();
    });
    connect(this, &DDaemonAudioManager::SinksChanged, this, [this](const QList<QDBusObjectPath> &paths) {
        Q_UNUSED(paths);
        updateOutputDevice();
    });
    connect(this, &DDaemonAudioManager::SourcesChanged, this, [this](const QList<QDBusObjectPath> &paths) {
        Q_UNUSED(paths);
        updateInputDevice();
    });

    connect(this, &DDaemonAudioManager::IncreaseVolumeChanged, this, &DAudioManagerPrivate::increaseVolumeChanged);
    connect(this, &DDaemonAudioManager::ReduceNoiseChanged, this, &DAudioManagerPrivate::reduceNoiseChanged);
    connect(this, &DDaemonAudioManager::MaxUIVolumeChanged, this, &DAudioManagerPrivate::maxVolumeChanged);

    connect(this, &DDaemonAudioManager::DefaultSourceChanged, this, [this](const QDBusObjectPath &path) {
        const auto &deviceName = DDaemonInternal::deviceName(path.path());
        qDebug() << "Default input device changed :" << deviceName;
        for (auto item : m_inputDevices) {
            const bool isDefault = item->name() == deviceName;
            item->setDefault(isDefault);
        }
        Q_EMIT defaultInputDeviceChanged(deviceName);
    });
    connect(this, &DDaemonAudioManager::DefaultSinkChanged, this, [this](const QDBusObjectPath &path) {
        const auto &deviceName = DDaemonInternal::deviceName(path.path());
        qDebug() << "Default output device changed :" << deviceName;
        for (auto item : m_outputDevices) {
            const bool isDefault = item->name() == deviceName;
            item->setDefault(isDefault);
        }
        Q_EMIT defaultOutputDeviceChanged(deviceName);
    });

    connect(this, &DDaemonAudioManager::PortEnableChanged, this, [this](quint32 cardIndex, const QString &portName, bool enabled) {
        if (auto card = cardByName(QString::number(cardIndex))) {
            if (auto port = card->portByName(portName)) {
                port->setEnabled(enabled);
            }
        }
    });
}

DDaemonAudioManager::~DDaemonAudioManager()
{

}

void DDaemonAudioManager::reset()
{
    m_inter->call("Reset");
}

void DDaemonAudioManager::setReConnectionEnabled(const bool enable)
{
    if (!enable) {
        m_inter->call("NoRestartPulseAudio");
    } else {
        qWarning() << "Don't support to switch, it's default action.";
    }
}

bool DDaemonAudioManager::increaseVolume() const
{
    return qdbus_cast<bool>(m_inter->property("IncreaseVolume"));
}

bool DDaemonAudioManager::reduceNoise() const
{
    return qdbus_cast<bool>(m_inter->property("ReduceNoise"));
}

double DDaemonAudioManager::maxVolume() const
{
    return qdbus_cast<double>(m_inter->property("MaxUIVolume"));
}

void DDaemonAudioManager::setIncreaseVolume(bool increaseVolume)
{
    m_inter->setProperty("IncreaseVolume", increaseVolume);
}

void DDaemonAudioManager::setReduceNoise(bool reduceNoise)
{
    m_inter->setProperty("ReduceNoise", reduceNoise);
}

void DDaemonAudioManager::updateCards()
{
    qDebug() << Q_FUNC_INFO;
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
    qDebug() << Q_FUNC_INFO;

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
        addInputDevice(device);
    }
}

void DDaemonAudioManager::updateOutputDevice()
{
    qDebug() << Q_FUNC_INFO;

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
        addOutputDevice(device);
    }
}

void DDaemonAudioManager::updateOutputStream()
{
    qDebug() << Q_FUNC_INFO;

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
            if (item->name() == QString::number(sinkIndex)) {
                device = item.data();
                break;
            }
        }
        if (!device) {
            qWarning() << "Don't find inputDevice for the outputStream" << path;
            return;
        }
        auto stream = new DDaemonOutputStream(path, device);
        device->addStream(stream);
    }
}

void DDaemonAudioManager::updateInputStream()
{
    qDebug() << Q_FUNC_INFO;

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
                device = item.data();
                break;
            }
        }
        if (!device) {
            qWarning() << "Don't find outputDevice for the inputStream" << path;
            return;
        }
        auto stream = new DDaemonInputStream(path, device);
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
