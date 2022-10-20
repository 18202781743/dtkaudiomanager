// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "daudiostream.h"
#include "daudiostream_p.h"
#include "daudiodevice.h"

#include <QDebug>

DAUDIOMANAGER_BEGIN_NAMESPACE

DAudioStream::DAudioStream(DAudioDevice *parent)
    : QObject (parent)
{

}

DAudioStream::~DAudioStream()
{

}

DAudioInputStream::DAudioInputStream(DPlatformAudioInputStream *d, DAudioDevice *parent)
    : DAudioStream (parent)
    , d(d)
{
    Q_ASSERT(d);

    connect(d, &DPlatformAudioInputStream::muteChanged, this, &DAudioInputStream::muteChanged);
    connect(d, &DPlatformAudioInputStream::fadeChanged, this, &DAudioInputStream::fadeChanged);
    connect(d, &DPlatformAudioInputStream::volumeChanged, this, &DAudioInputStream::volumeChanged);
    connect(d, &DPlatformAudioInputStream::balanceChanged, this, &DAudioInputStream::balanceChanged);

    connect(d, &DPlatformAudioInputStream::supportBalanceChanged, this, &DAudioInputStream::supportBalanceChanged);
    connect(d, &DPlatformAudioInputStream::supportFadeChanged, this, &DAudioInputStream::supportFadeChanged);
    connect(d, &DPlatformAudioInputStream::cardChanged, this, &DAudioInputStream::cardChanged);
}

DAudioInputStream::~DAudioInputStream()
{

}

bool DAudioInputStream::mute() const
{
    return d->mute();
}

double DAudioInputStream::fade() const
{
    return d->fade();
}

double DAudioInputStream::volume() const
{
    return d->volume();
}

double DAudioInputStream::balance() const
{
    return d->balance();
}

bool DAudioInputStream::supportBalance() const
{
    return d->supportBalance();
}

bool DAudioInputStream::supportFade() const
{
    return d->supportFade();
}

QString DAudioInputStream::card() const
{
    return d->card();
}

QString DAudioInputStream::name() const
{
    return d->name();
}

void DAudioInputStream::setMute(bool mute)
{
    d->setMute(mute);
}

void DAudioInputStream::setFade(double fade)
{
    d->setFade(fade);
}

void DAudioInputStream::setVolume(double volume)
{
    d->setVolume(volume);
}

void DAudioInputStream::setBalance(double balance)
{
    d->setBalance(balance);
}

DAudioOutputStream::DAudioOutputStream(DPlatformAudioOutputStream *d, DAudioDevice *parent)
    : DAudioStream (parent)
    , d(d)
{
    Q_ASSERT(d);

    connect(d, &DPlatformAudioOutputStream::muteChanged, this, &DAudioOutputStream::muteChanged);
    connect(d, &DPlatformAudioOutputStream::fadeChanged, this, &DAudioOutputStream::fadeChanged);
    connect(d, &DPlatformAudioOutputStream::volumeChanged, this, &DAudioOutputStream::volumeChanged);
    connect(d, &DPlatformAudioOutputStream::balanceChanged, this, &DAudioOutputStream::balanceChanged);

    connect(d, &DPlatformAudioOutputStream::supportBalanceChanged, this, &DAudioOutputStream::supportBalanceChanged);
    connect(d, &DPlatformAudioOutputStream::supportFadeChanged, this, &DAudioOutputStream::supportFadeChanged);
    connect(d, &DPlatformAudioOutputStream::cardChanged, this, &DAudioOutputStream::cardChanged);
}

DAudioOutputStream::~DAudioOutputStream()
{

}

bool DAudioOutputStream::mute() const
{
    return d->mute();
}

double DAudioOutputStream::fade() const
{
    return d->fade();
}

double DAudioOutputStream::volume() const
{
    return d->volume();
}

double DAudioOutputStream::balance() const
{
    return d->balance();
}

bool DAudioOutputStream::supportBalance() const
{
    return d->supportBalance();
}

bool DAudioOutputStream::supportFade() const
{
    return d->supportFade();
}

QString DAudioOutputStream::card() const
{
    return d->card();
}

QString DAudioOutputStream::name() const
{
    return d->name();
}

void DAudioOutputStream::setMute(bool mute)
{
    d->setMute(mute);
}

void DAudioOutputStream::setFade(double fade)
{
    d->setFade(fade);
}

void DAudioOutputStream::setVolume(double volume)
{
    d->setVolume(volume);
}

void DAudioOutputStream::setBalance(double balance)
{
    d->setBalance(balance);
}

DPlatformAudioInputStream::DPlatformAudioInputStream(DPlatformAudioOutputDevice *parent)
{

}

DPlatformAudioInputStream::~DPlatformAudioInputStream()
{
}

DPlatformAudioOutputStream::DPlatformAudioOutputStream(DPlatformAudioInputDevice *parent)
{

}

DPlatformAudioOutputStream::~DPlatformAudioOutputStream()
{
}

QString DPlatformAudioStream::name() const
{
    return m_name;
}

void DPlatformAudioStream::setName(const QString &name)
{
    m_name = name;
}

DAUDIOMANAGER_END_NAMESPACE
