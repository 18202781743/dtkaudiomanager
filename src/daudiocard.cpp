// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "daudiocard.h"
#include "daudiocard_p.h"
#include "daudioport_p.h"
#include "daudioport.h"
#include "daudiofactory_p.h"

#include <QDebug>

DAUDIOMANAGER_BEGIN_NAMESPACE

DAudioCard::DAudioCard(DPlatformAudioCard *d)
    : d(d)
{
    Q_ASSERT(d);
    connect(d, &DPlatformAudioCard::enabledChanged, this, &DAudioCard::enabledChanged);
}

DAudioCard::~DAudioCard()
{

}

QList<DAudioPort *> DAudioCard::ports() const
{
    QList<DAudioPort *> result;
    for (auto item : d->ports())
        result << item->source();

    return result;
}

QString DAudioCard::name() const
{
    return d->name();
}

bool DAudioCard::enabled() const
{
    return d->enabled();
}

DAudioBluetoothCard::DAudioBluetoothCard(DPlatformAudioBluetoothCard *d)
    : DAudioCard (d)
{
}

QString DAudioBluetoothCard::mode() const
{
    return dynamic_cast<DPlatformAudioBluetoothCard *>(d)->mode();
}

QStringList DAudioBluetoothCard::modeOptions() const
{
    return dynamic_cast<DPlatformAudioBluetoothCard *>(d)->modeOptions();
}

void DAudioBluetoothCard::setMode(QString mode)
{
    return dynamic_cast<DPlatformAudioBluetoothCard *>(d)->setMode(mode);
}
DAUDIOMANAGER_END_NAMESPACE
