// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "daudiodevice_daemon.h"
#include "daudiostream.h"
#include "daudiocard.h"
#include "daemonhelpers.hpp"

#include <QDBusAbstractInterface>
#include <QDBusArgument>
#include <QDBusReply>
#include <QDebug>

DAUDIOMANAGER_BEGIN_NAMESPACE

DDaemonAudioInputDevice::DDaemonAudioInputDevice(const QString &path, DPlatformAudioCard *card)
    : DPlatformAudioInputDevice (card)
    , m_inter(DDaemonInternal::newAudioInterface(path, DDaemonInternal::AudioServiceSourceInterface))
{
    setName(DDaemonInternal::deviceName(path));
}

DDaemonAudioInputDevice::~DDaemonAudioInputDevice()
{

}

bool DDaemonAudioInputDevice::mute() const
{
    return qdbus_cast<bool>(m_inter->property("Mute"));
}

double DDaemonAudioInputDevice::fade() const
{
    return qdbus_cast<double>(m_inter->property("Fade"));
}

double DDaemonAudioInputDevice::volume() const
{
    return qdbus_cast<double>(m_inter->property("Volume"));
}

double DDaemonAudioInputDevice::balance() const
{
    return qdbus_cast<double>(m_inter->property("Balance"));
}

bool DDaemonAudioInputDevice::supportBalance() const
{
    return qdbus_cast<bool>(m_inter->property("SupportBalance"));
}

bool DDaemonAudioInputDevice::supportFade() const
{
    return qdbus_cast<bool>(m_inter->property("SupportFade"));
}

double DDaemonAudioInputDevice::baseVolume() const
{
    return qdbus_cast<bool>(m_inter->property("BaseVolume"));
}

double DDaemonAudioInputDevice::meterVolume() const
{
    const_cast<DDaemonAudioInputDevice *>(this)->ensureMeter();

    return m_meterInter ? qdbus_cast<double>(m_meterInter->property("Volume")) : 0.0;
}

void DDaemonAudioInputDevice::setMute(bool mute)
{
    m_inter->call("SetMute", mute);
}

void DDaemonAudioInputDevice::setFade(double fade)
{
    m_inter->call("SetFade", fade);
}

void DDaemonAudioInputDevice::setVolume(double volume)
{
    m_inter->call("SetVolume", volume);
}

void DDaemonAudioInputDevice::setBalance(double balance)
{
    m_inter->call("SetBalance", balance);
}

void DDaemonAudioInputDevice::ensureMeter()
{
    if (m_meterInter && !m_meterInter->isValid()) {
        m_meterInter.reset();
    }
    if (!m_meterInter) {

        QDBusReply<QDBusObjectPath> reply = m_inter->call("GetMeter");
        if (!reply.isValid()) {
            qWarning() << "Can't get Meter" << reply.error();
            return;
        }
        const auto path = reply.value().path();
        auto inter = DDaemonInternal::newAudioInterface(path, DDaemonInternal::AudioServiceMeterInterface);
        if (!inter->isValid()) {
            qWarning() << "Error:" << inter->lastError();
            inter->deleteLater();
            return;
        }
        m_meterInter.reset(inter);
    }
    m_meterInter->call("Tick");
}

DDaemonAudioOutputDevice::DDaemonAudioOutputDevice(const QString &path, DPlatformAudioCard *parent)
    : DPlatformAudioOutputDevice (parent)
    , m_inter(DDaemonInternal::newAudioInterface2(this, path, DDaemonInternal::AudioServiceSinkInterface))
{
    setName(DDaemonInternal::deviceName(path));

    connect(this, &DDaemonAudioOutputDevice::MuteChanged, this, &DPlatformAudioOutputDevice::muteChanged);
    connect(this, &DDaemonAudioOutputDevice::FadeChanged, this, &DPlatformAudioOutputDevice::fadeChanged);
    connect(this, &DDaemonAudioOutputDevice::VolumeChanged, this, &DPlatformAudioOutputDevice::volumeChanged);
    connect(this, &DDaemonAudioOutputDevice::BalanceChanged, this, &DPlatformAudioOutputDevice::balanceChanged);

    connect(this, &DDaemonAudioOutputDevice::SupportBalanceChanged, this, &DPlatformAudioOutputDevice::supportBalanceChanged);
    connect(this, &DDaemonAudioOutputDevice::SupportFadeChanged, this, &DPlatformAudioOutputDevice::supportFadeChanged);
    connect(this, &DDaemonAudioOutputDevice::BaseVolumeChanged, this, &DPlatformAudioOutputDevice::baseVolumeChanged);
}

DDaemonAudioOutputDevice::~DDaemonAudioOutputDevice()
{
}

bool DDaemonAudioOutputDevice::mute() const
{
    return qdbus_cast<bool>(m_inter->property("Mute"));
}

double DDaemonAudioOutputDevice::fade() const
{
    return qdbus_cast<double>(m_inter->property("Fade"));
}

double DDaemonAudioOutputDevice::volume() const
{
    return qdbus_cast<double>(m_inter->property("Volume"));
}

double DDaemonAudioOutputDevice::balance() const
{
    return qdbus_cast<double>(m_inter->property("Balance"));
}

bool DDaemonAudioOutputDevice::supportBalance() const
{
    return qdbus_cast<bool>(m_inter->property("SupportBalance"));
}

bool DDaemonAudioOutputDevice::supportFade() const
{
    return qdbus_cast<bool>(m_inter->property("SupportFade"));
}

double DDaemonAudioOutputDevice::baseVolume() const
{
    return qdbus_cast<double>(m_inter->property("BaseVolume"));
}

double DDaemonAudioOutputDevice::meterVolume() const
{
    return 0.0;
}

void DDaemonAudioOutputDevice::setMute(bool mute)
{
    m_inter->call("SetMute", mute);
}

void DDaemonAudioOutputDevice::setFade(double fade)
{
    m_inter->call("SetFade", fade);
}

void DDaemonAudioOutputDevice::setVolume(double volume)
{
    m_inter->call("SetVolume", volume);
}

void DDaemonAudioOutputDevice::setBalance(double balance)
{
    m_inter->call("SetBalance", balance);
}

DAUDIOMANAGER_END_NAMESPACE

