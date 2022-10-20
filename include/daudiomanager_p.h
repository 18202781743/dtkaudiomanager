// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "dtkaudiomanager_global.h"
#include "daudiomanager.h"
#include "daudiocard_p.h"
#include "daudiodevice_p.h"
#include "daudiostream_p.h"

#include <QObject>

DAUDIOMANAGER_BEGIN_NAMESPACE
class DPlatformAudioCard;
class DAudioInputDevice;
class DAudioOutputDevice;

class LIBDTKAUDIOMANAGERSHARED_EXPORT DAudioManagerPrivate : public QObject
{
    Q_OBJECT

public:

    virtual void reset() = 0;
    virtual void setReConnectionEnabled(const bool enable) = 0;
    virtual void setPort(const QString& card, const QString &portName, const int direction) = 0;
    virtual void setPortEnabled(const QString& card, const QString &portName) = 0;

    virtual bool increaseVolume() const = 0;
    virtual bool reduceNoise() const = 0;
    virtual double maxVolume() const = 0;

    void addCard(DPlatformAudioCard *card)
    {
        m_cards.append(QExplicitlySharedDataPointer(card));
        Q_EMIT cardsChanged();
    }
    void removeCard(const QString &cardName)
    {
        for (auto item : m_cards) {
            if (item->name() == cardName) {
                m_cards.removeOne(item);
                Q_EMIT cardsChanged();
                break;
            }
        }
    }
    void addInputDevice(DPlatformAudioInputDevice *device)
    {
        m_inputDevices.append(QExplicitlySharedDataPointer(device));
        Q_EMIT deviceAdded(device->name(), true);
    }
    void removeInputDevice(const QString &deviceName)
    {
        for (auto item : m_inputDevices) {
            if (item->name() == deviceName) {
                m_inputDevices.removeOne(item);
                deviceRemoved(deviceName, true);
                break;
            }
        }
    }

    void addOutputDevice(DPlatformAudioOutputDevice *device)
    {
        m_outputDevices.append(QExplicitlySharedDataPointer(device));
        Q_EMIT deviceAdded(device->name(), false);
    }
    void removeOutputDevice(const QString &deviceName)
    {
        for (auto item : m_outputDevices) {
            if (item->name() == deviceName) {
                m_outputDevices.removeOne(item);
                deviceRemoved(deviceName, false);
                break;
            }
        }
    }

public Q_SLOTS:
    virtual void setIncreaseVolume(bool increaseVolume) = 0;
    virtual void setReduceNoise(bool reduceNoise) = 0;

Q_SIGNALS:
    void deviceAdded(const QString &name, const bool isInputDevice);
    void deviceRemoved(const QString &name, const bool isInputDevice);
    void cardsChanged();

    void increaseVolumeChanged(bool increaseVolume);
    void reduceNoiseChanged(bool reduceNoise);
    void maxVolumeChanged(bool maxVolume);

public:
    QList<QExplicitlySharedDataPointer<DPlatformAudioCard>> m_cards;
    QList<QExplicitlySharedDataPointer<DPlatformAudioInputDevice>> m_inputDevices;
    QList<QExplicitlySharedDataPointer<DPlatformAudioOutputDevice>> m_outputDevices;

};
DAUDIOMANAGER_END_NAMESPACE
