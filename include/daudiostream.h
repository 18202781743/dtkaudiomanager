// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "dtkaudiomanager_global.h"

#include <QObject>

DAUDIOMANAGER_BEGIN_NAMESPACE
class DAudioDevice;
class DAudioStreamPrivate;
class LIBDTKAUDIOMANAGERSHARED_EXPORT DAudioStream : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool mute READ mute WRITE setMute NOTIFY muteChanged)
    Q_PROPERTY(double fade READ fade WRITE setFade NOTIFY fadeChanged)
    Q_PROPERTY(double volume READ volume WRITE setVolume NOTIFY volumeChanged)
    Q_PROPERTY(double balance READ balance WRITE setBalance NOTIFY balanceChanged)
    Q_PROPERTY(bool supportBalance READ supportBalance NOTIFY supportBalanceChanged)
    Q_PROPERTY(bool supportFade READ supportFade NOTIFY supportFadeChanged)
    Q_PROPERTY(double meterVolume READ meterVolume NOTIFY meterVolumeChanged)
    Q_PROPERTY(QString card READ card NOTIFY cardChanged)
public:
    explicit DAudioStream(DAudioDevice *parent = nullptr);
    virtual ~DAudioStream() override;

    virtual bool mute() const = 0;
    virtual double fade() const = 0;
    virtual double volume() const = 0;
    virtual double balance() const = 0;

    virtual bool supportBalance() const = 0;
    virtual bool supportFade() const = 0;
    virtual double meterVolume() const = 0;

    virtual QString card() const = 0;

public Q_SLOTS:
    virtual void setMute(bool mute) = 0;
    virtual void setFade(double fade) = 0;
    virtual void setVolume(double volume) = 0;
    virtual void setBalance(double balance) = 0;

Q_SIGNALS:
    void muteChanged(bool mute);
    void fadeChanged(double fade);
    void volumeChanged(double volume);
    void balanceChanged(double balance);

    void supportBalanceChanged(bool supportBalance);
    void supportFadeChanged(bool supportFade);
    void meterVolumeChanged(double meterVolume);

    void cardChanged(QString card);

private:
    Q_DISABLE_COPY(DAudioStream)
    Q_DECLARE_PRIVATE(DAudioStream)
};

class DPlatformAudioInputStream;
class LIBDTKAUDIOMANAGERSHARED_EXPORT DAudioInputStream : public DAudioStream
{
    Q_OBJECT

public:
    explicit DAudioInputStream(DPlatformAudioInputStream *d, DAudioDevice *parent = nullptr);
    virtual ~DAudioInputStream() override;

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
    DPlatformAudioInputStream *d = nullptr;
};

class DPlatformAudioOutputStream;
class LIBDTKAUDIOMANAGERSHARED_EXPORT DAudioOutputStream : public DAudioStream
{
    Q_OBJECT

public:
    explicit DAudioOutputStream(DPlatformAudioOutputStream *d, DAudioDevice *parent = nullptr);
    virtual ~DAudioOutputStream() override;

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
    DPlatformAudioOutputStream *d = nullptr;
};
DAUDIOMANAGER_END_NAMESPACE
