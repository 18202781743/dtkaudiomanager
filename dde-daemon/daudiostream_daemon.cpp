// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "daudiostream_daemon.h"
#include "daudiodevice.h"
#include "daemonhelpers.hpp"

#include <QDebug>

DAUDIOMANAGER_BEGIN_NAMESPACE

DDaemonInputStream::DDaemonInputStream(const QString &path, DPlatformAudioOutputDevice *parent)
    : DPlatformAudioInputStream (parent)
    , m_inter(new DDBusInterface(DDaemonInternal::AudioServiceName, path))
{

}

DDaemonInputStream::~DDaemonInputStream()
{

}

bool DDaemonInputStream::mute() const
{
    return false;
}

double DDaemonInputStream::fade() const
{
    return 0.0;
}

double DDaemonInputStream::volume() const
{
    return 0.0;
}

double DDaemonInputStream::balance() const
{
    return 0.0;
}

bool DDaemonInputStream::supportBalance() const
{
    return false;
}

bool DDaemonInputStream::supportFade() const
{
    return false;
}

double DDaemonInputStream::meterVolume() const
{
    return 0.0;
}

void DDaemonInputStream::setMute(bool mute)
{

}

void DDaemonInputStream::setFade(double fade)
{

}

void DDaemonInputStream::setVolume(double volume)
{

}

void DDaemonInputStream::setBalance(double balance)
{

}

DDaemonOutputStream::DDaemonOutputStream(const QString &path, DPlatformAudioInputDevice *parent)
    : DPlatformAudioOutputStream (parent)
    , m_inter(new DDBusInterface(DDaemonInternal::AudioServiceName, path))
{

}

DDaemonOutputStream::~DDaemonOutputStream()
{

}

bool DDaemonOutputStream::mute() const
{
    return false;
}

double DDaemonOutputStream::fade() const
{
    return 0.0;
}

double DDaemonOutputStream::volume() const
{
    return 0.0;
}

double DDaemonOutputStream::balance() const
{
    return 0.0;
}

bool DDaemonOutputStream::supportBalance() const
{
    return false;
}

bool DDaemonOutputStream::supportFade() const
{
    return false;
}

double DDaemonOutputStream::meterVolume() const
{
    return 0.0;
}

void DDaemonOutputStream::setMute(bool mute)
{

}

void DDaemonOutputStream::setFade(double fade)
{

}

void DDaemonOutputStream::setVolume(double volume)
{

}

void DDaemonOutputStream::setBalance(double balance)
{

}
DAUDIOMANAGER_END_NAMESPACE
