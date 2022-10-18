// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "namespace.h"
#include "daudiomanager.h"
#include "daudiocard_p.h"
#include "daudiodevice_p.h"

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
    virtual bool maxVolume() const = 0;

public Q_SLOTS:
    void setIncreaseVolume(bool increaseVolume);
    void setReduceNoise(bool reduceNoise);

Q_SIGNALS:
    void deviceAdded(const QString &name, const bool isInputDevice);
    void deviceRemoved(const QString &name, const bool isInputDevice);

    void increaseVolumeChanged(bool increaseVolume);
    void reduceNoiseChanged(bool reduceNoise);
    void maxVolumeChanged(bool maxVolume);

public:
    QList<DPlatformAudioCard *> m_cards;
    QList<DPlatformAudioInputDevice *> m_inputDevices;
    QList<DPlatformAudioOutputDevice *> m_outputDevices;

};
DAUDIOMANAGER_END_NAMESPACE
