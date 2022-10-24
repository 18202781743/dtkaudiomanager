// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "dtkaudiomanager_global.h"
#include <QObject>
#include <QSharedPointer>

DAUDIOMANAGER_BEGIN_NAMESPACE
class DAudioCard;
class DAudioInputDevice;
class DAudioOutputDevice;
using DAudioCardPtr = QSharedPointer<DAudioCard>;
using DAudioInputDevicePtr = QSharedPointer<DAudioInputDevice>;
using DAudioOutputDevicePtr = QSharedPointer<DAudioOutputDevice>;

class DAudioManagerPrivate;
class LIBDTKAUDIOMANAGERSHARED_EXPORT DAudioManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool increaseVolume READ increaseVolume WRITE setIncreaseVolume NOTIFY increaseVolumeChanged)
    Q_PROPERTY(bool reduceNoise READ reduceNoise WRITE setReduceNoise NOTIFY reduceNoiseChanged)
    Q_PROPERTY(double maxVolume READ maxVolume NOTIFY maxVolumeChanged)
public:
    explicit DAudioManager(QObject *parent = nullptr);
    explicit DAudioManager(DAudioManagerPrivate *d, QObject *parent = nullptr);
    virtual ~DAudioManager() override;

    QList<DAudioCardPtr> cards() const;
    DAudioCardPtr card(const QString &cardName) const;
    QList<DAudioCardPtr> availableCards() const;
    QList<DAudioInputDevicePtr> inputDevices() const;
    QList<DAudioOutputDevicePtr> outputDevices() const;
    DAudioInputDevicePtr defaultInputDevice() const;
    DAudioOutputDevicePtr defaultOutputDevice() const;
    DAudioInputDevicePtr inputDevice(const QString &deviceName) const;
    DAudioOutputDevicePtr outputDevice(const QString &deviceName) const;

    void reset();
    void setReConnectionEnabled(const bool enable);
    void setPort(const QString& cardName, const QString &portName);
    void setPortEnabled(const QString& cardName, const QString &portName, bool enabled);

    bool increaseVolume() const;
    bool reduceNoise() const;
    double maxVolume() const;

public Q_SLOTS:
    void setIncreaseVolume(bool increaseVolume);
    void setReduceNoise(bool reduceNoise);

Q_SIGNALS:
    void deviceAdded(const QString &name, const bool isInputDevice);
    void deviceRemoved(const QString &name, const bool isInputDevice);
    void cardsChanged();
    void defaultInputDeviceChanged(const QString &name);
    void defaultOutputDeviceChanged(const QString &name);

    void increaseVolumeChanged(bool increaseVolume);
    void reduceNoiseChanged(bool reduceNoise);
    void maxVolumeChanged(bool maxVolume);

private:
    Q_DISABLE_COPY(DAudioManager)
    QScopedPointer<DAudioManagerPrivate> d;
};
DAUDIOMANAGER_END_NAMESPACE

