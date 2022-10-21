// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "daudiostream.h"
#include "daudiostream_p.h"
#include "daudiodevice.h"
#include "daudiodevice_p.h"

#include <QDebug>

DAUDIOMANAGER_BEGIN_NAMESPACE

DAudioStream::DAudioStream(DPlatformAudioStream *d, DAudioDevice *parent)
    : QObject (parent)
    , d(d)
{
    Q_ASSERT(d);

    connect(d, &DPlatformAudioStream::muteChanged, this, &DAudioStream::muteChanged);
    connect(d, &DPlatformAudioStream::fadeChanged, this, &DAudioStream::fadeChanged);
    connect(d, &DPlatformAudioStream::volumeChanged, this, &DAudioStream::volumeChanged);
    connect(d, &DPlatformAudioStream::balanceChanged, this, &DAudioStream::balanceChanged);

    connect(d, &DPlatformAudioStream::supportBalanceChanged, this, &DAudioStream::supportBalanceChanged);
    connect(d, &DPlatformAudioStream::supportFadeChanged, this, &DAudioStream::supportFadeChanged);
    connect(d, &DPlatformAudioStream::cardChanged, this, &DAudioStream::cardChanged);
}

DAudioStream::~DAudioStream()
{

}

bool DAudioStream::mute() const
{
    return d->mute();
}

double DAudioStream::fade() const
{
    return d->fade();
}

double DAudioStream::volume() const
{
    return d->volume();
}

double DAudioStream::balance() const
{
    return d->balance();
}

bool DAudioStream::supportBalance() const
{
    return d->supportBalance();
}

bool DAudioStream::supportFade() const
{
    return d->supportFade();
}

QString DAudioStream::card() const
{
    return d->card();
}

QString DAudioStream::name() const
{
    return d->name();
}

void DAudioStream::setMute(bool mute)
{
    d->setMute(mute);
}

void DAudioStream::setFade(double fade)
{
    d->setFade(fade);
}

void DAudioStream::setVolume(double volume)
{
    d->setVolume(volume);
}

void DAudioStream::setBalance(double balance)
{
    d->setBalance(balance);
}

DAudioInputStream::DAudioInputStream(DPlatformAudioInputStream *d, DAudioDevice *parent)
    : DAudioStream (d, parent)
{
}

DAudioInputStream::~DAudioInputStream()
{

}

DAudioOutputStream::DAudioOutputStream(DPlatformAudioOutputStream *d, DAudioDevice *parent)
    : DAudioStream (d, parent)
{
}

DAudioOutputStream::~DAudioOutputStream()
{

}

DPlatformAudioStream::DPlatformAudioStream(DPlatformAudioDevice *parent)
    : m_device(parent)
{

}

QString DPlatformAudioStream::card() const
{
    if (m_device) {
        return m_device->card();
    }
    return QString();
}

QString DPlatformAudioStream::name() const
{
    return m_name;
}

void DPlatformAudioStream::setName(const QString &name)
{
    m_name = name;
}

DPlatformAudioInputStream::DPlatformAudioInputStream(DPlatformAudioOutputDevice *parent)
    : DPlatformAudioStream(parent)
{

}

DPlatformAudioInputStream::~DPlatformAudioInputStream()
{

}

DPlatformAudioOutputStream::DPlatformAudioOutputStream(DPlatformAudioInputDevice *parent)
    : DPlatformAudioStream(parent)
{

}

DPlatformAudioOutputStream::~DPlatformAudioOutputStream()
{

}

DAUDIOMANAGER_END_NAMESPACE
