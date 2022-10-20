// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "dtkaudiomanager_global.h"
#include "daudiostream_p.h"
#include "daudiodevice_p.h"
#include "dbus/ddbusinterface.h"

#include <QObject>

DAUDIOMANAGER_BEGIN_NAMESPACE
class DAudioDevice;

class DPlatformAudioInputStream;
class LIBDTKAUDIOMANAGERSHARED_EXPORT DDaemonInputStream : public DPlatformAudioInputStream
{
    Q_OBJECT

public:
    explicit DDaemonInputStream(const QString &path, DPlatformAudioOutputDevice *parent = nullptr);
    virtual ~DDaemonInputStream() override;

    virtual bool mute() const override;
    virtual double fade() const override;
    virtual double volume() const override;
    virtual double balance() const override;
    virtual bool supportBalance() const override;
    virtual bool supportFade() const override;
    virtual double meterVolume() const override;

    virtual QString card() const override;

public Q_SLOTS:
    virtual void setMute(bool mute) override;
    virtual void setFade(double fade) override;
    virtual void setVolume(double volume) override;
    virtual void setBalance(double balance) override;

private:
    DPlatformAudioOutputDevice *m_device;
    QDBusInterface *m_inter = nullptr;
};

class DPlatformAudioOutputStream;
class LIBDTKAUDIOMANAGERSHARED_EXPORT DDaemonOutputStream : public DPlatformAudioOutputStream
{
    Q_OBJECT

public:
    explicit DDaemonOutputStream(const QString &path, DPlatformAudioInputDevice *parent = nullptr);
    virtual ~DDaemonOutputStream() override;

    virtual bool mute() const override;
    virtual double fade() const override;
    virtual double volume() const override;
    virtual double balance() const override;
    virtual bool supportBalance() const override;
    virtual bool supportFade() const override;
    virtual double meterVolume() const override;

    virtual QString card() const override;

public Q_SLOTS:
    virtual void setMute(bool mute) override;
    virtual void setFade(double fade) override;
    virtual void setVolume(double volume) override;
    virtual void setBalance(double balance) override;

private:
    DPlatformAudioInputDevice *m_device;
    QDBusInterface *m_inter = nullptr;
};
DAUDIOMANAGER_END_NAMESPACE
