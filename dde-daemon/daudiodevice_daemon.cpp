// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "daudiodevice_daemon.h"
#include "daudiostream.h"
#include "daudiocard.h"

#include <QDBusAbstractInterface>
#include <QDBusArgument>
#include <QDebug>

DAUDIOMANAGER_BEGIN_NAMESPACE

DDaemonAudioInputDevice::DDaemonAudioInputDevice(const QString &path, DPlatformAudioCard *card)
    : DPlatformAudioInputDevice (card)
    , m_inter(new DDBusInterface("com.deepin.daemon.Audio", path))
{
}

bool DDaemonAudioInputDevice::mute() const
{
    return qdbus_cast<bool>(m_inter->property("mute"));
}

double DDaemonAudioInputDevice::fade() const
{
    return qdbus_cast<double>(m_inter->property("fade"));
}

double DDaemonAudioInputDevice::volume() const
{
    return qdbus_cast<double>(m_inter->property("volume"));
}

double DDaemonAudioInputDevice::balance() const
{
    return 0.0;
}

bool DDaemonAudioInputDevice::supportBalance() const
{
    return false;
}

bool DDaemonAudioInputDevice::supportFade() const
{
    return false;
}

double DDaemonAudioInputDevice::baseVolume() const
{
    return 0.0;
}

void DDaemonAudioInputDevice::setMute(bool mute)
{

}

void DDaemonAudioInputDevice::setFade(double fade)
{

}

void DDaemonAudioInputDevice::setVolume(double volume)
{

}

void DDaemonAudioInputDevice::setBalance(double balance)
{

}

bool DDaemonAudioOutputDevice::mute() const
{
    return false;
}

double DDaemonAudioOutputDevice::fade() const
{
    return 0.0;
}

double DDaemonAudioOutputDevice::volume() const
{
    return 0.0;
}

double DDaemonAudioOutputDevice::balance() const
{
    return 0.0;
}

bool DDaemonAudioOutputDevice::supportBalance() const
{
    return false;
}

bool DDaemonAudioOutputDevice::supportFade() const
{
    return false;
}

double DDaemonAudioOutputDevice::baseVolume() const
{
    return 0.0;
}

void DDaemonAudioOutputDevice::setMute(bool mute)
{

}

void DDaemonAudioOutputDevice::setFade(double fade)
{

}

void DDaemonAudioOutputDevice::setVolume(double volume)
{

}

void DDaemonAudioOutputDevice::setBalance(double balance)
{

}

DAUDIOMANAGER_END_NAMESPACE

