// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "daudioport.h"
#include "daudioport_p.h"
#include "daudiocard_p.h"

#include "daudiofactory_p.h"

#include <QDebug>

DAUDIOMANAGER_BEGIN_NAMESPACE

DAudioPort::DAudioPort(DPlatformAudioPort *d)
    :d(d)
{
    Q_ASSERT(d);

    connect(d, &DPlatformAudioPort::nameChanged, this, &DAudioPort::nameChanged);
    connect(d, &DPlatformAudioPort::descriptionChanged, this, &DAudioPort::descriptionChanged);
}

DAudioPort::~DAudioPort()
{

}

void DAudioPort::setEnabled(const bool enabled)
{
    d->setEnabled(enabled);
}

bool DAudioPort::isEnabled() const
{
    return d->isEnabled();
}

int DAudioPort::direction() const
{
    return d->direction();
}

QString DAudioPort::name() const
{
    return d->name();
}

QString DAudioPort::description() const
{
    return d->description();
}

DPlatformAudioPort::DPlatformAudioPort(DPlatformAudioCard *card)
    : m_card(card)
{
    if (m_card) {
        m_card->addPort(this);
    }
}

DPlatformAudioPort::~DPlatformAudioPort()
{
}

bool DPlatformAudioPort::isActive() const
{
    return m_isActive;
}

void DPlatformAudioPort::setActive(const int active)
{
    m_isActive = active;
}

int DPlatformAudioPort::direction() const
{
    return m_direction;
}

void DPlatformAudioPort::setDirection(const int direction)
{
    m_direction = direction;
}

DAUDIOMANAGER_END_NAMESPACE
