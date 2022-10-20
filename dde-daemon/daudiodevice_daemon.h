// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "dtkaudiomanager_global.h"
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

    virtual double meterVolume() const override;

public Q_SLOTS:
    virtual void setMute(bool mute) override;
    virtual void setFade(double fade) override;
    virtual void setVolume(double volume) override;
    virtual void setBalance(double balance) override;

private:
    void ensureMeter();

private:
    QDBusInterface *m_inter = nullptr;
    QDBusInterface *m_meterInter = nullptr;
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

    virtual double meterVolume() const override;

public Q_SLOTS:
    virtual void setMute(bool mute) override;
    virtual void setFade(double fade) override;
    virtual void setVolume(double volume) override;
    virtual void setBalance(double balance) override;

private:
    QDBusInterface *m_inter = nullptr;
};
DAUDIOMANAGER_END_NAMESPACE
