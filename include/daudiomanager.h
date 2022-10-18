// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "dtkaudiomanager_global.h"

#include <QObject>

DAUDIOMANAGER_BEGIN_NAMESPACE
class DAudioCard;
class DAudioInputDevice;
class DAudioOutputDevice;

class DAudioManagerPrivate;
class LIBDTKAUDIOMANAGERSHARED_EXPORT DAudioManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool increaseVolume READ increaseVolume WRITE setIncreaseVolume NOTIFY increaseVolumeChanged)
    Q_PROPERTY(bool reduceNoise READ reduceNoise WRITE setReduceNoise NOTIFY reduceNoiseChanged)
    Q_PROPERTY(bool maxVolume READ maxVolume NOTIFY maxVolumeChanged)
public:
    explicit DAudioManager(QObject *parent = nullptr);
    virtual ~DAudioManager() override;

    QList<DAudioCard*> cards() const;
    QList<DAudioCard*> availableCards() const;
    QList<DAudioInputDevice*> inputDevices() const;
    QList<DAudioOutputDevice*> outputDevices() const;
    DAudioInputDevice *defaultInputDevice() const;
    DAudioOutputDevice *defaultOutputDevice() const;
    QList<DAudioInputDevice*> availableInputDevices() const;
    QList<DAudioOutputDevice*> availableOutputDevices() const;
    DAudioInputDevice *inputDevice(const QString &deviceName) const;
    DAudioOutputDevice *outputDevice(const QString &deviceName) const;

    void reset();
    void setReConnectionEnabled(const bool enable);
    void setPort(const QString& card, const QString &portName, const int direction);
    void setPortEnabled(const QString& card, const QString &portName);

    bool increaseVolume() const;
    bool reduceNoise() const;
    bool maxVolume() const;

public Q_SLOTS:
    void setIncreaseVolume(bool increaseVolume);
    void setReduceNoise(bool reduceNoise);

Q_SIGNALS:
    void deviceAdded(const QString &name, const bool isInputDevice);
    void deviceRemoved(const QString &name, const bool isInputDevice);

    void increaseVolumeChanged(bool increaseVolume);
    void reduceNoiseChanged(bool reduceNoise);
    void maxVolumeChanged(bool maxVolume);

private:
    Q_DISABLE_COPY(DAudioManager)
    Q_DECLARE_PRIVATE(DAudioManager)
    DAudioManagerPrivate *d = nullptr;
};
DAUDIOMANAGER_END_NAMESPACE
