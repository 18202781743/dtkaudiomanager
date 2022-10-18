// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "daudioport.h"
#include "daudioport_p.h"

#include "daudiofactory_p.h"

#include <QDebug>

DAUDIOMANAGER_BEGIN_NAMESPACE

DAudioPort::DAudioPort(DPlatformAudioPort *d)
    :d(d)
{
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
    return QString();
}
DAUDIOMANAGER_END_NAMESPACE
