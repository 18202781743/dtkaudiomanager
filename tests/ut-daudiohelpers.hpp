// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "gtest/gtest.h"

#include "daudioport.h"
#include "daudioport_p.h"

#include "daudiocard.h"
#include "daudiocard_p.h"

#include "daudiodevice.h"
#include "daudiodevice_p.h"

#include "daudiostream.h"
#include "daudiostream_p.h"

#include "daudiostream.h"
#include "daudiomanager_p.h"

#include <QPointer>

DAUDIOMANAGER_USE_NAMESPACE

static const QString TestAudioPortName("test port");
static const QString TestAudioPortDescription("port for testing");
class TestAudioPort : public DPlatformAudioPort
{
public:
    explicit TestAudioPort(DPlatformAudioCard *card = nullptr, const QString &name = TestAudioPortName)
        : DPlatformAudioPort(card)
        , m_name(name)
    {
    }
    inline virtual ~TestAudioPort() override;
    virtual void setEnabled(const bool enabled) override
    {
        m_enabled = enabled;
    }
    virtual bool isEnabled() const override
    {
        return m_enabled;
    }
    virtual int direction() const override
    {
        return 1;
    }
    virtual QString name() const override
    {
        return m_name;
    }
    virtual QString description() const override
    {
        return TestAudioPortDescription;
    }

    QString m_name;
    bool m_enabled = false;
};

TestAudioPort::~TestAudioPort() {}

static const QString TestAudioCardName("test card");
class TestAudioCard : public DPlatformAudioCard
{
public:
    explicit TestAudioCard(const QString &name = TestAudioCardName)
        : DPlatformAudioCard()
        , m_name(name)
    {
    }
    inline virtual ~TestAudioCard() override;
    virtual bool enabled() const override
    {
        return m_enabled;
    }
    virtual QString name() const override
    {
        return m_name;
    }
    void setEnabled(bool enabled)
    {
        if (m_enabled == enabled)
            return;
        m_enabled = enabled;
        Q_EMIT enabledChanged(m_enabled);
    }

    QString m_name;
    bool m_enabled = false;
};

TestAudioCard::~TestAudioCard() {}

static const QString TestAudioInputDeviceName("test input device");
static const QString TestAudioInputDeviceDescription("input device for testing");
class TestAudioInputDevice : public DPlatformAudioInputDevice
{
public:
    explicit TestAudioInputDevice()
    {
        setName(TestAudioInputDeviceName);
        setDescription(TestAudioInputDeviceDescription);
    }
    inline virtual ~TestAudioInputDevice() override;

    virtual bool mute() const override
    {
        return m_mute;
    }
    virtual double fade() const override
    {
        return m_fade;
    }
    virtual double volume() const override
    {
        return m_volume;
    }
    virtual double balance() const override
    {
        return m_balance;
    }
    virtual bool supportBalance() const override
    {
        return m_supportBalance;
    }
    virtual bool supportFade() const override
    {
        return m_supportFade;
    }
    virtual double baseVolume() const override
    {
        return m_baseVolume;
    }

public Q_SLOTS:
    virtual void setMute(bool mute) override
    {
        if (m_mute == mute)
            return;
        m_mute = mute;
        Q_EMIT muteChanged(m_mute);
    }
    virtual void setFade(double fade) override
    {
        if (qFuzzyCompare(m_fade, fade))
            return;
        m_fade = fade;
        Q_EMIT fadeChanged(m_fade);
    }
    virtual void setVolume(double volume) override
    {
        m_volume = volume;
    }
    virtual void setBalance(double balance) override
    {
        m_balance = balance;
    }
    virtual double meterVolume() const override
    {
        return m_meterVolume;
    }

public:
    bool m_mute = false;
    double m_fade = 1.0;
    double m_volume = 1.0;
    double m_balance = 1.0;
    bool m_supportBalance = false;
    bool m_supportFade = false;
    double m_baseVolume = 1.0;
    double m_meterVolume = 1.0;
};

TestAudioInputDevice::~TestAudioInputDevice() {}

static const QString TestAudioOutputDeviceName("test output device");
static const QString TestAudioOutputDeviceDescription("output device for testing");
class TestAudioOutputDevice : public DPlatformAudioOutputDevice
{
public:
    explicit TestAudioOutputDevice()
    {
        setName(TestAudioOutputDeviceName);
        setDescription(TestAudioOutputDeviceDescription);
    }
    inline virtual ~TestAudioOutputDevice() override;

    virtual bool mute() const override
    {
        return m_mute;
    }
    virtual double fade() const override
    {
        return m_fade;
    }
    virtual double volume() const override
    {
        return m_volume;
    }
    virtual double balance() const override
    {
        return m_balance;
    }
    virtual bool supportBalance() const override
    {
        return m_supportBalance;
    }
    virtual bool supportFade() const override
    {
        return m_supportFade;
    }
    virtual double baseVolume() const override
    {
        return m_baseVolume;
    }
    virtual double meterVolume() const override
    {
        return m_meterVolume;
    }

public Q_SLOTS:
    virtual void setMute(bool mute) override
    {
        if (m_mute == mute)
            return;
        m_mute = mute;
        Q_EMIT muteChanged(m_mute);
    }
    virtual void setFade(double fade) override
    {
        if (qFuzzyCompare(m_fade, fade))
            return;
        m_fade = fade;
        Q_EMIT fadeChanged(m_fade);
    }
    virtual void setVolume(double volume) override
    {
        m_volume = volume;
    }
    virtual void setBalance(double balance) override
    {
        m_balance = balance;
    }

public:
    bool m_mute = false;
    double m_fade = 1.0;
    double m_volume = 1.0;
    double m_balance = 1.0;
    bool m_supportBalance = false;
    bool m_supportFade = false;
    double m_baseVolume = 1.0;
    double m_meterVolume = 1.0;
};

TestAudioOutputDevice::~TestAudioOutputDevice() {}

static const QString TestAudioInputStreamName("test input  stream device");
static const QString TestAudioInputStreamDescription("input stream for testing");
class TestAudioInputStream: public DPlatformAudioInputStream
{
public:
    explicit TestAudioInputStream(DPlatformAudioOutputDevice *parent = nullptr)
        : DPlatformAudioInputStream(parent)
    {
    }

    inline virtual ~TestAudioInputStream() override;

    virtual bool mute() const override
    {
        return m_mute;
    }
    virtual double fade() const override
    {
        return m_fade;
    }
    virtual double volume() const override
    {
        return m_volume;
    }
    virtual double balance() const override
    {
        return m_balance;
    }
    virtual bool supportBalance() const override
    {
        return m_supportBalance;
    }
    virtual bool supportFade() const override
    {
        return m_supportFade;
    }
    virtual QString card() const override
    {
        return m_card;
    }

public Q_SLOTS:
    virtual void setMute(bool mute) override
    {
        if (m_mute == mute)
            return;
        m_mute = mute;
        Q_EMIT muteChanged(m_mute);
    }
    virtual void setFade(double fade) override
    {
        if (qFuzzyCompare(m_fade, fade))
            return;
        m_fade = fade;
        Q_EMIT fadeChanged(m_fade);
    }
    virtual void setVolume(double volume) override
    {
        m_volume = volume;
    }
    virtual void setBalance(double balance) override
    {
        m_balance = balance;
    }

public:
    bool m_mute = false;
    double m_fade = 1.0;
    double m_volume = 1.0;
    double m_balance = 1.0;
    bool m_supportBalance = false;
    bool m_supportFade = false;
    double m_meterVolume = 1.0;
    QString m_card;
};

TestAudioInputStream::~TestAudioInputStream() {}

static const QString TestAudioOutputStreamName("test input  stream device");
static const QString TestAudioOutputStreamDescription("input stream for testing");
class TestAudioOutputStream: public DPlatformAudioOutputStream
{
public:
    explicit TestAudioOutputStream(DPlatformAudioInputDevice *parent = nullptr)
        : DPlatformAudioOutputStream(parent)
    {
    }

    inline virtual ~TestAudioOutputStream() override;

    virtual bool mute() const override
    {
        return m_mute;
    }
    virtual double fade() const override
    {
        return m_fade;
    }
    virtual double volume() const override
    {
        return m_volume;
    }
    virtual double balance() const override
    {
        return m_balance;
    }
    virtual bool supportBalance() const override
    {
        return m_supportBalance;
    }
    virtual bool supportFade() const override
    {
        return m_supportFade;
    }
    virtual QString card() const override
    {
        return m_card;
    }

public Q_SLOTS:
    virtual void setMute(bool mute) override
    {
        if (m_mute == mute)
            return;
        m_mute = mute;
        Q_EMIT muteChanged(m_mute);
    }
    virtual void setFade(double fade) override
    {
        if (qFuzzyCompare(m_fade, fade))
            return;
        m_fade = fade;
        Q_EMIT fadeChanged(m_fade);
    }
    virtual void setVolume(double volume) override
    {
        m_volume = volume;
    }
    virtual void setBalance(double balance) override
    {
        m_balance = balance;
    }

public:
    bool m_mute = false;
    double m_fade = 1.0;
    double m_volume = 1.0;
    double m_balance = 1.0;
    bool m_supportBalance = false;
    bool m_supportFade = false;
    double m_meterVolume = 1.0;
    QString m_card;
};

TestAudioOutputStream::~TestAudioOutputStream() {}

class TestAudioManager : public DAudioManagerPrivate
{
public:
    inline virtual ~TestAudioManager() override;

    virtual void reset() override
    {
    }
    virtual void setReConnectionEnabled(const bool enable) override
    {
    }
    virtual void setPort(const QString &card, const QString &portName, const int direction) override
    {
    }
    virtual void setPortEnabled(const QString &card, const QString &portName) override
    {
    }
    virtual bool increaseVolume() const override
    {
        return m_increaseVolume;
    }
    virtual bool reduceNoise() const override
    {
        return m_reduceNoise;
    }
    virtual double maxVolume() const override
    {
        return m_maxVolume;
    }

public slots:
    virtual void setIncreaseVolume(bool increaseVolume) override
    {
        m_increaseVolume = increaseVolume;
    }
    virtual void setReduceNoise(bool reduceNoise) override
    {
        m_reduceNoise = reduceNoise;
    }

public:
    bool m_reconnectionEnabled = false;
    bool m_increaseVolume = false;
    bool m_reduceNoise = false;
    double m_maxVolume = 1.0;
};

TestAudioManager::~TestAudioManager() {}
