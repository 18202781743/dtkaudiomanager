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

QList<DAudioPortPtr> DAudioCard::ports() const
{
    QList<DAudioPortPtr> result;
    for (auto item : d->m_ports)
        result << DAudioPortPtr(item->create());

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
    connect(d, &DPlatformAudioBluetoothCard::modeChanged, this, &DAudioBluetoothCard::modeChanged);
    connect(d, &DPlatformAudioBluetoothCard::modeOptionsChanged, this, &DAudioBluetoothCard::modeOptionsChanged);
}

QString DAudioBluetoothCard::mode() const
{
    return dynamic_cast<DPlatformAudioBluetoothCard *>(d.data())->mode();
}

QStringList DAudioBluetoothCard::modeOptions() const
{
    return dynamic_cast<DPlatformAudioBluetoothCard *>(d.data())->modeOptions();
}

void DAudioBluetoothCard::setMode(QString mode)
{
    return dynamic_cast<DPlatformAudioBluetoothCard *>(d.data())->setMode(mode);
}
DAUDIOMANAGER_END_NAMESPACE
