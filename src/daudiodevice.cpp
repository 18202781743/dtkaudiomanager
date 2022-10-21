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

DAudioDevice::DAudioDevice(DPlatformAudioDevice *d)
    : d(d)
{
    connect(d, &DPlatformAudioDevice::muteChanged, this, &DAudioDevice::muteChanged);
    connect(d, &DPlatformAudioDevice::fadeChanged, this, &DAudioDevice::fadeChanged);
    connect(d, &DPlatformAudioDevice::volumeChanged, this, &DAudioDevice::volumeChanged);
    connect(d, &DPlatformAudioDevice::balanceChanged, this, &DAudioDevice::balanceChanged);

    connect(d, &DPlatformAudioDevice::supportBalanceChanged, this, &DAudioDevice::supportBalanceChanged);
    connect(d, &DPlatformAudioDevice::supportFadeChanged, this, &DAudioDevice::supportFadeChanged);
    connect(d, &DPlatformAudioDevice::baseVolumeChanged, this, &DAudioDevice::baseVolumeChanged);

    connect(d, &DPlatformAudioDevice::meterVolumeChanged, this, &DAudioDevice::meterVolumeChanged);

    connect(d, &DPlatformAudioDevice::nameChanged, this, &DAudioDevice::nameChanged);
    connect(d, &DPlatformAudioDevice::descriptionChanged, this, &DAudioDevice::descriptionChanged);


    connect(d, &DPlatformAudioDevice::streamAdded, this, &DAudioDevice::streamAdded);
    connect(d, &DPlatformAudioDevice::streamRemoved, this, &DAudioDevice::streamRemoved);

}

DAudioDevice::~DAudioDevice()
{

}

bool DAudioDevice::mute() const
{
    return d->mute();
}

double DAudioDevice::fade() const
{
    return d->fade();
}

double DAudioDevice::volume() const
{
    return d->volume();
}

double DAudioDevice::balance() const
{
    return d->balance();
}

bool DAudioDevice::supportBalance() const
{
    return d->supportBalance();
}

bool DAudioDevice::supportFade() const
{
    return d->supportFade();
}

double DAudioDevice::baseVolume() const
{
    return d->baseVolume();
}

double DAudioDevice::meterVolume() const
{
    return d->meterVolume();
}

QString DAudioDevice::name() const
{
    return d->name();
}

QString DAudioDevice::description() const
{
    return d->description();
}

QString DAudioDevice::card() const
{
    return d->card();
}

QList<DAudioStreamPtr> DAudioDevice::streams() const
{
    QList<DAudioStreamPtr> result;
    for (auto item : d->m_streams) {
        result << DAudioStreamPtr(item->create());
    }
    return result;
}

DAudioStreamPtr DAudioDevice::stream(const QString &streamName) const
{
    QList<DAudioStreamPtr> result;
    for (auto item : d->m_streams) {
        if (item->name() == streamName)
            return DAudioStreamPtr(item->create());
    }
    return nullptr;
}

void DAudioDevice::setMute(bool mute)
{
    d->setMute(mute);
}

void DAudioDevice::setFade(double fade)
{
    d->setFade(fade);
}

void DAudioDevice::setVolume(double volume)
{
    d->setVolume(volume);
}

void DAudioDevice::setBalance(double balance)
{
    d->setBalance(balance);
}

DAudioInputDevice::DAudioInputDevice(DAudioCard *parent)
    : DAudioDevice (parent)
{

}

DAudioInputDevice::DAudioInputDevice(DPlatformAudioInputDevice *d)
    : DAudioDevice(d)
{
    Q_ASSERT(d);

}

DAudioOutputDevice::DAudioOutputDevice(DAudioCard *parent)
    : DAudioDevice (parent)
{

}

DAudioOutputDevice::DAudioOutputDevice(DPlatformAudioOutputDevice *d)
    : DAudioDevice(d)
{
}

DPlatformAudioInputDevice::DPlatformAudioInputDevice(DPlatformAudioCard *card)
    : DPlatformAudioDevice(card)
{
}

DPlatformAudioInputDevice::~DPlatformAudioInputDevice()
{
}

DPlatformAudioDevice::DPlatformAudioDevice(DPlatformAudioCard *card)
{

}

DPlatformAudioDevice::~DPlatformAudioDevice()
{

}

QString DPlatformAudioDevice::card() const
{
    if (m_card) {
        m_card->name();
    }
    return QString();
}

void DPlatformAudioDevice::addStream(DPlatformAudioStream *stream)
{
    m_streams.append(stream);
    Q_EMIT streamAdded(stream->name());
}

void DPlatformAudioDevice::removeStream(const QString &streamName)
{
    bool hasChanged = false;
    for (auto item : m_streams) {
        if (item->name() == streamName) {
            m_streams.removeOne(item);
            break;
        }
    }
    if (hasChanged) {
        Q_EMIT streamRemoved(streamName);
    }
}

QString DPlatformAudioDevice::name() const
{
    return m_name;
}

QString DPlatformAudioDevice::description() const
{
    return m_description;
}

void DPlatformAudioDevice::setName(const QString &name)
{
    if (name == m_name)
        return;
    m_name = name;
    Q_EMIT nameChanged(m_name);
}

void DPlatformAudioDevice::setDescription(const QString &description)
{
    if (description == m_description)
        return;
    m_description = description;
    Q_EMIT descriptionChanged(m_description);
}

DPlatformAudioOutputDevice::DPlatformAudioOutputDevice(DPlatformAudioCard *card)
    : DPlatformAudioDevice(card)
{
}

DPlatformAudioOutputDevice::~DPlatformAudioOutputDevice()
{
}
DAUDIOMANAGER_END_NAMESPACE
