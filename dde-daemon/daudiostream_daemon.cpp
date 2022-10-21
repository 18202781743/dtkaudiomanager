// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "daudiostream_daemon.h"
#include "daudiodevice.h"
#include "daemonhelpers.hpp"

#include <QDBusArgument>
#include <QDebug>

DAUDIOMANAGER_BEGIN_NAMESPACE

DDaemonInputStream::DDaemonInputStream(const QString &path, DPlatformAudioOutputDevice *parent)
    : DPlatformAudioInputStream (parent)
    , m_device(parent)
    , m_inter(DDaemonInternal::newAudioInterface(path, DDaemonInternal::AudioServiceSinkInputInterface))
{
    setName(DDaemonInternal::streamName(path));
}

DDaemonInputStream::~DDaemonInputStream()
{

}

bool DDaemonInputStream::mute() const
{
    return qdbus_cast<bool>(m_inter->property("Mute"));
}

double DDaemonInputStream::fade() const
{
    return qdbus_cast<double>(m_inter->property("fade"));
}

double DDaemonInputStream::volume() const
{
    return qdbus_cast<double>(m_inter->property("volume"));
}

double DDaemonInputStream::balance() const
{
    return qdbus_cast<double>(m_inter->property("balance"));
}

bool DDaemonInputStream::supportBalance() const
{
    return qdbus_cast<bool>(m_inter->property("supportBalance"));
}

bool DDaemonInputStream::supportFade() const
{
    return qdbus_cast<bool>(m_inter->property("supportFade"));
}

QString DDaemonInputStream::card() const
{

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
    , m_device(parent)
    , m_inter(DDaemonInternal::newAudioInterface(path, DDaemonInternal::AudioServiceSourceOutputInterface))
{
    setName(DDaemonInternal::streamName(path));
}

DDaemonOutputStream::~DDaemonOutputStream()
{

}

bool DDaemonOutputStream::mute() const
{
    return qdbus_cast<bool>(m_inter->property("Mute"));
}

double DDaemonOutputStream::fade() const
{
    return qdbus_cast<double>(m_inter->property("Fade"));
}

double DDaemonOutputStream::volume() const
{
    return qdbus_cast<double>(m_inter->property("Volume"));
}

double DDaemonOutputStream::balance() const
{
    return qdbus_cast<double>(m_inter->property("Balance"));
}

bool DDaemonOutputStream::supportBalance() const
{
    return qdbus_cast<bool>(m_inter->property("SupportBalance"));
}

bool DDaemonOutputStream::supportFade() const
{
    return qdbus_cast<bool>(m_inter->property("SupportFade"));
}

QString DDaemonOutputStream::card() const
{
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
