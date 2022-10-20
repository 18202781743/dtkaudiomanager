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

DAudioInputDevice::DAudioInputDevice(DPlatformAudioInputDevice *d)
    : d(d)
{
    Q_ASSERT(d);

    connect(d, &DPlatformAudioInputDevice::streamAdded, this, &DAudioInputDevice::streamAdded);
    connect(d, &DPlatformAudioInputDevice::streamRemoved, this, &DAudioInputDevice::streamRemoved);

    connect(d, &DPlatformAudioInputDevice::muteChanged, this, &DAudioInputDevice::muteChanged);
    connect(d, &DPlatformAudioInputDevice::fadeChanged, this, &DAudioInputDevice::fadeChanged);
    connect(d, &DPlatformAudioInputDevice::volumeChanged, this, &DAudioInputDevice::volumeChanged);
    connect(d, &DPlatformAudioInputDevice::balanceChanged, this, &DAudioInputDevice::balanceChanged);

    connect(d, &DPlatformAudioInputDevice::supportBalanceChanged, this, &DAudioInputDevice::supportBalanceChanged);
    connect(d, &DPlatformAudioInputDevice::supportFadeChanged, this, &DAudioInputDevice::supportFadeChanged);
    connect(d, &DPlatformAudioInputDevice::baseVolumeChanged, this, &DAudioInputDevice::baseVolumeChanged);

    connect(d, &DPlatformAudioInputDevice::nameChanged, this, &DAudioInputDevice::nameChanged);
    connect(d, &DPlatformAudioInputDevice::descriptionChanged, this, &DAudioInputDevice::descriptionChanged);
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

QString DAudioInputDevice::name() const
{
    return d->name();
}

QString DAudioInputDevice::description() const
{
    return d->description();
}

QList<DAudioOutputStreamPtr> DAudioInputDevice::streams() const
{
    QList<DAudioOutputStreamPtr> result;
    for (auto item : d->m_streams) {
        result << DAudioOutputStreamPtr(item->create());
    }
    return result;
}

DAudioOutputStreamPtr DAudioInputDevice::stream(const QString &streamName) const
{
    QList<DAudioOutputStreamPtr> result;
    for (auto item : d->m_streams) {
        if (item->name() == streamName)
            return DAudioOutputStreamPtr(item->create());
    }
    return nullptr;
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

DAudioInputDevice::DAudioInputDevice(DAudioCard *parent)
    : DAudioDevice (parent)
{

}

DAudioOutputDevice::DAudioOutputDevice(DAudioCard *parent)
    : DAudioDevice (parent)
{

}

DAudioOutputDevice::DAudioOutputDevice(DPlatformAudioOutputDevice *d)
    : d(d)
{
    Q_ASSERT(d);


    connect(d, &DPlatformAudioOutputDevice::streamAdded, this, &DAudioOutputDevice::streamAdded);
    connect(d, &DPlatformAudioOutputDevice::streamRemoved, this, &DAudioOutputDevice::streamRemoved);

    connect(d, &DPlatformAudioOutputDevice::muteChanged, this, &DAudioOutputDevice::muteChanged);
    connect(d, &DPlatformAudioOutputDevice::fadeChanged, this, &DAudioOutputDevice::fadeChanged);
    connect(d, &DPlatformAudioOutputDevice::volumeChanged, this, &DAudioOutputDevice::volumeChanged);
    connect(d, &DPlatformAudioOutputDevice::balanceChanged, this, &DAudioOutputDevice::balanceChanged);

    connect(d, &DPlatformAudioOutputDevice::supportBalanceChanged, this, &DAudioOutputDevice::supportBalanceChanged);
    connect(d, &DPlatformAudioOutputDevice::supportFadeChanged, this, &DAudioOutputDevice::supportFadeChanged);
    connect(d, &DPlatformAudioOutputDevice::baseVolumeChanged, this, &DAudioOutputDevice::baseVolumeChanged);

    connect(d, &DPlatformAudioOutputDevice::nameChanged, this, &DAudioOutputDevice::nameChanged);
    connect(d, &DPlatformAudioOutputDevice::descriptionChanged, this, &DAudioOutputDevice::descriptionChanged);
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

QString DAudioOutputDevice::name() const
{
    return d->name();
}

QString DAudioOutputDevice::description() const
{
    return d->description();
}

QList<DAudioInputStreamPtr> DAudioOutputDevice::streams() const
{
    QList<DAudioInputStreamPtr> result;
    for (auto item : d->m_streams) {
        result << DAudioInputStreamPtr(item->create());
    }
    return result;
}

DAudioInputStreamPtr DAudioOutputDevice::stream(const QString &streamName)
{
    QList<DAudioInputStreamPtr> result;
    for (auto item : d->m_streams) {
        if (item->name() == streamName)
            return DAudioInputStreamPtr(item->create());
    }
    return nullptr;
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
