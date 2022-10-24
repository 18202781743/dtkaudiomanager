// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "dtkaudiomanager_global.h"
#include "daudiocard_p.h"
#include "daudiodevice_p.h"
#include "daudiostream_p.h"

#include <QObject>
#include <QSharedDataPointer>

DAUDIOMANAGER_BEGIN_NAMESPACE
class DPlatformAudioCard;
class DPlatformAudioInputDevice;
class DPlatformAudioOutputDevice;
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

    void addCard(DPlatformAudioCard *card);
    void removeCard(const QString &cardName);
    void addInputDevice(DPlatformAudioInputDevice *device);
    void removeInputDevice(const QString &deviceName);
    void addOutputDevice(DPlatformAudioOutputDevice *device);
    void removeOutputDevice(const QString &deviceName);

public Q_SLOTS:
    virtual void setIncreaseVolume(bool increaseVolume) = 0;
    virtual void setReduceNoise(bool reduceNoise) = 0;

Q_SIGNALS:
    void deviceAdded(const QString &name, const bool isInputDevice);
    void deviceRemoved(const QString &name, const bool isInputDevice);
    void cardsChanged();
    void defaultInputDeviceChanged(const QString &name);
    void defaultOutputDeviceChanged(const QString &name);

    void increaseVolumeChanged(bool increaseVolume);
    void reduceNoiseChanged(bool reduceNoise);
    void maxVolumeChanged(double maxVolume);

public:
    QList<QExplicitlySharedDataPointer<DPlatformAudioCard>> m_cards;
    QList<QExplicitlySharedDataPointer<DPlatformAudioInputDevice>> m_inputDevices;
    QList<QExplicitlySharedDataPointer<DPlatformAudioOutputDevice>> m_outputDevices;
};
DAUDIOMANAGER_END_NAMESPACE
