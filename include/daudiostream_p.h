// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "namespace.h"
#include "daudiostream.h"
#include "daudiodevice_p.h"

#include <QObject>

DAUDIOMANAGER_BEGIN_NAMESPACE
class DAudioDevice;
class LIBDTKAUDIOMANAGERSHARED_EXPORT DPlatformAudioStream : public QObject
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
    explicit DPlatformAudioStream(DAudioDevice *parent = nullptr);
    virtual ~DPlatformAudioStream() override;

    virtual bool mute() const = 0;
    virtual double fade() const = 0;
    virtual double volume() const = 0;
    virtual double balance() const = 0;

    virtual bool supportBalance() const = 0;
    virtual bool supportFade() const = 0;
    virtual double meterVolume() const = 0;

    QString card() const;

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
};

class LIBDTKAUDIOMANAGERSHARED_EXPORT DPlatformAudioInputStream : public DPlatformAudioStream
{
    Q_OBJECT

public:
    explicit DPlatformAudioInputStream(DPlatformAudioOutputDevice *parent = nullptr);

    DAudioInputStream *source()
    {
        if (!m_source) {
            m_source = new DAudioInputStream(this);
        }
        return m_source;
    }

protected:
    DAudioInputStream *m_source = nullptr;
};

class LIBDTKAUDIOMANAGERSHARED_EXPORT DPlatformAudioOutputStream : public DPlatformAudioStream
{
    Q_OBJECT

public:
    explicit DPlatformAudioOutputStream(DPlatformAudioInputDevice *parent = nullptr);

    DAudioOutputStream *source()
    {
        if (!m_source) {
            m_source = new DAudioOutputStream(this);
        }
        return m_source;
    }
protected:
    DAudioOutputStream *m_source = nullptr;
};
DAUDIOMANAGER_END_NAMESPACE
