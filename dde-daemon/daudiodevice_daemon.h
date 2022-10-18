// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "namespace.h"
#include "daudiodevice_p.h"
#include "dbus/ddbusinterface.h"

#include <QObject>

DAUDIOMANAGER_BEGIN_NAMESPACE
class DAudioCard;
class DAudioDevicePrivate;
class LIBDTKAUDIOMANAGERSHARED_EXPORT DDaemonAudioInputDevice : public DPlatformAudioInputDevice
{
    Q_OBJECT
public:
    explicit DDaemonAudioInputDevice(const QString &path, DPlatformAudioCard *card = nullptr);
    virtual ~DDaemonAudioInputDevice() override;

    virtual bool mute() const override;
    virtual double fade() const override;
    virtual double volume() const override;
    virtual double balance() const override;

    virtual bool supportBalance() const override;
    virtual bool supportFade() const override;
    virtual double baseVolume() const override;

    virtual QString name() const override;
    virtual QString description() const override;

public Q_SLOTS:
    virtual void setMute(bool mute) override;
    virtual void setFade(double fade) override;
    virtual void setVolume(double volume) override;
    virtual void setBalance(double balance) override;

Q_SIGNALS:
    void streamAdded(const QString &name);
    void streamRemoved(const QString &name);

    void muteChanged(bool mute);
    void fadeChanged(double fade);
    void volumeChanged(double volume);
    void balanceChanged(double balance);

    void supportBalanceChanged(bool supportBalance);
    void supportFadeChanged(bool supportFade);
    void baseVolumeChanged(double baseVolume);

    void nameChanged(QString name);
    void descriptionChanged(QString description);

private:
    DDBusInterface *m_inter = nullptr;
};

class LIBDTKAUDIOMANAGERSHARED_EXPORT DDaemonAudioOutputDevice : public DPlatformAudioOutputDevice
{
    Q_OBJECT
public:
    explicit DDaemonAudioOutputDevice(const QString &path, DPlatformAudioCard *parent = nullptr);
    virtual ~DDaemonAudioOutputDevice() override;

    virtual bool mute() const override;
    virtual double fade() const override;
    virtual double volume() const override;
    virtual double balance() const override;

    virtual bool supportBalance() const override;
    virtual bool supportFade() const override;
    virtual double baseVolume() const override;

    virtual QString name() const override;
    virtual QString description() const override;

public Q_SLOTS:
    virtual void setMute(bool mute) override;
    virtual void setFade(double fade) override;
    virtual void setVolume(double volume) override;
    virtual void setBalance(double balance) override;

Q_SIGNALS:
    void streamAdded(const QString &name);
    void streamRemoved(const QString &name);

    void muteChanged(bool mute);
    void fadeChanged(double fade);
    void volumeChanged(double volume);
    void balanceChanged(double balance);

    void supportBalanceChanged(bool supportBalance);
    void supportFadeChanged(bool supportFade);
    void baseVolumeChanged(double baseVolume);

    void nameChanged(QString name);
    void descriptionChanged(QString description);

private:
    DDBusInterface *m_inter = nullptr;
};
DAUDIOMANAGER_END_NAMESPACE
