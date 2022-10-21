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

DDAemonDeviceInterface::DDAemonDeviceInterface(DDBusInterface *inter, DPlatformAudioDevice *owner)
    : m_inter(inter)
    , m_owner(owner)
{
    connect(this, &DDAemonDeviceInterface::MuteChanged, m_owner, &DPlatformAudioDevice::muteChanged);
    connect(this, &DDAemonDeviceInterface::FadeChanged, m_owner, &DPlatformAudioDevice::fadeChanged);
    connect(this, &DDAemonDeviceInterface::VolumeChanged, m_owner, &DPlatformAudioDevice::volumeChanged);
    connect(this, &DDAemonDeviceInterface::BalanceChanged, m_owner, &DPlatformAudioDevice::balanceChanged);

    connect(this, &DDAemonDeviceInterface::SupportBalanceChanged, m_owner, &DPlatformAudioDevice::supportBalanceChanged);
    connect(this, &DDAemonDeviceInterface::SupportFadeChanged, m_owner, &DPlatformAudioDevice::supportFadeChanged);
    connect(this, &DDAemonDeviceInterface::BaseVolumeChanged, m_owner, &DPlatformAudioDevice::baseVolumeChanged);
}

bool DDAemonDeviceInterface::mute() const
{
    return qdbus_cast<bool>(m_inter->property("Mute"));
}

double DDAemonDeviceInterface::fade() const
{
    return qdbus_cast<double>(m_inter->property("Fade"));
}

double DDAemonDeviceInterface::volume() const
{
    return qdbus_cast<double>(m_inter->property("Volume"));
}

double DDAemonDeviceInterface::balance() const
{
    return qdbus_cast<double>(m_inter->property("Balance"));
}

bool DDAemonDeviceInterface::supportBalance() const
{
    return qdbus_cast<bool>(m_inter->property("SupportBalance"));
}

bool DDAemonDeviceInterface::supportFade() const
{
    return qdbus_cast<bool>(m_inter->property("SupportFade"));
}

double DDAemonDeviceInterface::baseVolume() const
{
    return qdbus_cast<bool>(m_inter->property("BaseVolume"));
}

void DDAemonDeviceInterface::setMute(bool mute)
{
    m_inter->call("SetMute", mute);
}

void DDAemonDeviceInterface::setFade(double fade)
{
    m_inter->call("SetFade", fade);
}

void DDAemonDeviceInterface::setVolume(double volume)
{
    m_inter->call("SetVolume", volume, true);
}

void DDAemonDeviceInterface::setBalance(double balance)
{
    m_inter->call("SetBalance", balance);
}

DDaemonAudioInputDevice::DDaemonAudioInputDevice(const QString &path, DPlatformAudioCard *card)
    : DPlatformAudioInputDevice (card)
    , m_interface(new DDAemonDeviceInterface(
                      DDaemonInternal::newAudioInterface2(
                          this, path, DDaemonInternal::AudioServiceSourceInterface),
                      this))
{
    setName(DDaemonInternal::deviceName(path));
}

DDaemonAudioInputDevice::~DDaemonAudioInputDevice()
{

}

bool DDaemonAudioInputDevice::mute() const
{
    return m_interface->mute();
}

double DDaemonAudioInputDevice::fade() const
{
    return m_interface->fade();
}

double DDaemonAudioInputDevice::volume() const
{
    return m_interface->volume();
}

double DDaemonAudioInputDevice::balance() const
{
    return m_interface->balance();
}

bool DDaemonAudioInputDevice::supportBalance() const
{
    return m_interface->supportBalance();
}

bool DDaemonAudioInputDevice::supportFade() const
{
    return m_interface->supportFade();
}

double DDaemonAudioInputDevice::baseVolume() const
{
    return m_interface->baseVolume();
}

double DDaemonAudioInputDevice::meterVolume() const
{
    const_cast<DDaemonAudioInputDevice *>(this)->ensureMeter();

    return m_meterInter ? qdbus_cast<double>(m_meterInter->property("Volume")) : 0.0;
}

void DDaemonAudioInputDevice::setMute(bool mute)
{
    m_interface->setMute(mute);
}

void DDaemonAudioInputDevice::setFade(double fade)
{
    m_interface->setFade(fade);
}

void DDaemonAudioInputDevice::setVolume(double volume)
{
    m_interface->setVolume(volume);
}

void DDaemonAudioInputDevice::setBalance(double balance)
{
    m_interface->setBalance(balance);
}

void DDaemonAudioInputDevice::ensureMeter()
{
    if (m_meterInter && !m_meterInter->isValid()) {
        m_meterInter.reset();
    }
    if (!m_meterInter) {

        QDBusReply<QDBusObjectPath> reply = m_interface->m_inter->call("GetMeter");
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
    , m_interface(new DDAemonDeviceInterface(
                      DDaemonInternal::newAudioInterface2(
                          this, path, DDaemonInternal::AudioServiceSinkInterface),
                      this))
{
    setName(DDaemonInternal::deviceName(path));
}

DDaemonAudioOutputDevice::~DDaemonAudioOutputDevice()
{
}

bool DDaemonAudioOutputDevice::mute() const
{
    return m_interface->mute();
}

double DDaemonAudioOutputDevice::fade() const
{
    return m_interface->fade();
}

double DDaemonAudioOutputDevice::volume() const
{
    return m_interface->volume();
}

double DDaemonAudioOutputDevice::balance() const
{
    return m_interface->balance();
}

bool DDaemonAudioOutputDevice::supportBalance() const
{
    return m_interface->supportBalance();
}

bool DDaemonAudioOutputDevice::supportFade() const
{
    return m_interface->supportFade();
}

double DDaemonAudioOutputDevice::baseVolume() const
{
    return m_interface->baseVolume();
}

double DDaemonAudioOutputDevice::meterVolume() const
{
    return 0.0;
}

void DDaemonAudioOutputDevice::setMute(bool mute)
{
    m_interface->setMute(mute);
}

void DDaemonAudioOutputDevice::setFade(double fade)
{
    m_interface->setFade(fade);
}

void DDaemonAudioOutputDevice::setVolume(double volume)
{
    m_interface->setVolume(volume);
}

void DDaemonAudioOutputDevice::setBalance(double balance)
{
    m_interface->setBalance(balance);
}

DAUDIOMANAGER_END_NAMESPACE

