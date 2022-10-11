// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "namespace.h"

#include <QObject>

DAUDIOMANAGER_BEGIN_NAMESPACE
class DAudioCard;
class DAudioDevicePrivate;
class LIBDTKAUDIOMANAGERSHARED_EXPORT DAudioDevice : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool mute READ mute WRITE setMute NOTIFY muteChanged)
    Q_PROPERTY(double fade READ fade WRITE setFade NOTIFY fadeChanged)
    Q_PROPERTY(double volume READ volume WRITE setVolume NOTIFY volumeChanged)
    Q_PROPERTY(double balance READ balance WRITE setBalance NOTIFY balanceChanged)
    Q_PROPERTY(bool supportBalance READ supportBalance NOTIFY supportBalanceChanged)
    Q_PROPERTY(bool supportFade READ supportFade NOTIFY supportFadeChanged)
    Q_PROPERTY(double baseVolume READ baseVolume NOTIFY baseVolumeChanged)
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(QString description READ description NOTIFY descriptionChanged)
public:
    explicit DAudioDevice(DAudioCard *parent = nullptr);
    virtual ~DAudioDevice() override;

    virtual bool mute() const = 0;
    virtual double fade() const = 0;
    virtual double volume() const = 0;
    virtual double balance() const = 0;

    virtual bool supportBalance() const = 0;
    virtual bool supportFade() const = 0;
    virtual double baseVolume() const = 0;

    QString name() const;
    QString description() const;

public Q_SLOTS:
    virtual void setMute(bool mute) = 0;
    virtual void setFade(double fade) = 0;
    virtual void setVolume(double volume) = 0;
    virtual void setBalance(double balance) = 0;

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
    Q_DISABLE_COPY(DAudioDevice)
    Q_DECLARE_PRIVATE(DAudioDevice)
};

class DAudioInputDevicePrivate;
class LIBDTKAUDIOMANAGERSHARED_EXPORT DAudioInputDevice : public DAudioDevice
{
    Q_OBJECT

public:
    explicit DAudioInputDevice(DAudioDevice *parent = nullptr);

    virtual bool mute() const override;
    virtual double fade() const override;
    virtual double volume() const override;
    virtual double balance() const override;
    virtual bool supportBalance() const override;
    virtual bool supportFade() const override;
    virtual double baseVolume() const override;

public Q_SLOTS:
    virtual void setMute(bool mute) override;
    virtual void setFade(double fade) override;
    virtual void setVolume(double volume) override;
    virtual void setBalance(double balance) override;

private:
    Q_DISABLE_COPY(DAudioInputDevice)
    Q_DECLARE_PRIVATE(DAudioInputDevice)
};

class DAudioOutputDevicePrivate;
class LIBDTKAUDIOMANAGERSHARED_EXPORT DAudioOutputDevice : public DAudioDevice
{
    Q_OBJECT

public:
    explicit DAudioOutputDevice(DAudioDevice *parent = nullptr);

    virtual bool mute() const override;
    virtual double fade() const override;
    virtual double volume() const override;
    virtual double balance() const override;
    virtual bool supportBalance() const override;
    virtual bool supportFade() const override;
    virtual double baseVolume() const override;

public Q_SLOTS:
    virtual void setMute(bool mute) override;
    virtual void setFade(double fade) override;
    virtual void setVolume(double volume) override;
    virtual void setBalance(double balance) override;

private:
    Q_DISABLE_COPY(DAudioOutputDevice)
    Q_DECLARE_PRIVATE(DAudioOutputDevice)
};
DAUDIOMANAGER_END_NAMESPACE
