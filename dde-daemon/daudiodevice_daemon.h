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
class DDAemonDeviceInterface : public QObject
{
    Q_OBJECT
public:
    explicit DDAemonDeviceInterface(DDBusInterface *inter, DPlatformAudioDevice *owner = nullptr);

    bool mute() const;
    double fade() const;
    double volume() const;
    double balance() const;
    bool supportBalance() const;
    bool supportFade() const;
    double baseVolume() const;

public Q_SLOTS:
    void setMute(bool mute);
    void setFade(double fade);
    void setVolume(double volume);
    void setBalance(double balance);

Q_SIGNALS:
    void MuteChanged(bool mute);
    void FadeChanged(double fade);
    void VolumeChanged(double volume);
    void BalanceChanged(double balance);

    void SupportBalanceChanged(bool supportBalance);
    void SupportFadeChanged(bool supportFade);
    void BaseVolumeChanged(double baseVolume);

public:
     QScopedPointer<DDBusInterface> m_inter;
     DPlatformAudioDevice *m_owner = nullptr;
};
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
    QScopedPointer<DDAemonDeviceInterface> m_interface;
    QScopedPointer<QDBusInterface> m_meterInter;
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
    QScopedPointer<DDAemonDeviceInterface> m_interface;
};
DAUDIOMANAGER_END_NAMESPACE
