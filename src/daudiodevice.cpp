// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "daudiodevice.h"
#include "daudiostream.h"
#include "daudiocard.h"

#include <QDebug>

DAUDIOMANAGER_BEGIN_NAMESPACE

DAudioDevice::DAudioDevice(DAudioCard *parent)
    : QObject (parent)
{

}

DAudioDevice::~DAudioDevice()
{

}

QString DAudioDevice::name() const
{
    return QString();
}

QString DAudioDevice::description() const
{
    return QString();
}

bool DAudioInputDevice::mute() const
{
    return false;
}

double DAudioInputDevice::fade() const
{
    return 0.0;
}

double DAudioInputDevice::volume() const
{
    return 0.0;
}

double DAudioInputDevice::balance() const
{
    return 0.0;
}

bool DAudioInputDevice::supportBalance() const
{
    return false;
}

bool DAudioInputDevice::supportFade() const
{
    return false;
}

double DAudioInputDevice::baseVolume() const
{
    return 0.0;
}

void DAudioInputDevice::setMute(bool mute)
{

}

void DAudioInputDevice::setFade(double fade)
{

}

void DAudioInputDevice::setVolume(double volume)
{

}

void DAudioInputDevice::setBalance(double balance)
{

}

bool DAudioOutputDevice::mute() const
{
    return false;
}

double DAudioOutputDevice::fade() const
{
    return 0.0;
}

double DAudioOutputDevice::volume() const
{
    return 0.0;
}

double DAudioOutputDevice::balance() const
{
    return 0.0;
}

bool DAudioOutputDevice::supportBalance() const
{
    return false;
}

bool DAudioOutputDevice::supportFade() const
{
    return false;
}

double DAudioOutputDevice::baseVolume() const
{
    return 0.0;
}

void DAudioOutputDevice::setMute(bool mute)
{

}

void DAudioOutputDevice::setFade(double fade)
{

}

void DAudioOutputDevice::setVolume(double volume)
{

}

void DAudioOutputDevice::setBalance(double balance)
{

}

DAUDIOMANAGER_END_NAMESPACE

