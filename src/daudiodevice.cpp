// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "daudiodevice.h"
#include "daudiostream.h"
#include "daudiocard.h"
#include "daudiodevice_p.h"

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

DAudioInputDevice::DAudioInputDevice(DAudioCard *parent)
    : DAudioDevice (parent)
{

}

DAudioInputDevice::DAudioInputDevice(DPlatformAudioInputDevice *d)
    : d(d)
{

}

bool DAudioInputDevice::mute() const
{
    return d->mute();
}

double DAudioInputDevice::fade() const
{
    return d->fade();
}

double DAudioInputDevice::volume() const
{
    return d->volume();
}

double DAudioInputDevice::balance() const
{
    return d->balance();
}

bool DAudioInputDevice::supportBalance() const
{
    return d->supportBalance();
}

bool DAudioInputDevice::supportFade() const
{
    return d->supportFade();
}

double DAudioInputDevice::baseVolume() const
{
    return d->baseVolume();
}

void DAudioInputDevice::setMute(bool mute)
{
    d->setMute(mute);
}

void DAudioInputDevice::setFade(double fade)
{
    d->setFade(fade);
}

void DAudioInputDevice::setVolume(double volume)
{
    d->setVolume(volume);
}

void DAudioInputDevice::setBalance(double balance)
{
    d->setBalance(balance);
}

DAudioOutputDevice::DAudioOutputDevice(DAudioCard *parent)
    : DAudioDevice (parent)
{

}

DAudioOutputDevice::DAudioOutputDevice(DPlatformAudioOutputDevice *d)
    : d(d)
{

}

bool DAudioOutputDevice::mute() const
{
    return d->mute();
}

double DAudioOutputDevice::fade() const
{
    return d->fade();
}

double DAudioOutputDevice::volume() const
{
    return d->volume();
}

double DAudioOutputDevice::balance() const
{
    return d->balance();
}

bool DAudioOutputDevice::supportBalance() const
{
    return d->supportBalance();
}

bool DAudioOutputDevice::supportFade() const
{
    return d->supportFade();
}

double DAudioOutputDevice::baseVolume() const
{
    return d->baseVolume();
}

void DAudioOutputDevice::setMute(bool mute)
{
    d->setMute(mute);
}

void DAudioOutputDevice::setFade(double fade)
{
    d->setFade(fade);
}

void DAudioOutputDevice::setVolume(double volume)
{
    d->setVolume(volume);
}

void DAudioOutputDevice::setBalance(double balance)
{
    d->setBalance(balance);
}
DAUDIOMANAGER_END_NAMESPACE
