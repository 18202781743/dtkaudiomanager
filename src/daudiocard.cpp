// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "daudiocard.h"
#include "daudioport.h"

#include <QDebug>

DAUDIOMANAGER_BEGIN_NAMESPACE

DAudioCard::DAudioCard(QObject *parent)
    : QObject (parent)
{

}

DAudioCard::~DAudioCard()
{

}

QList<DAudioPort *> DAudioCard::ports() const
{
    return {};
}

QString DAudioCard::name() const
{
    return QString();
}

bool DAudioCard::enabled() const
{
    return false;
}

DAudioBluetoothCard::DAudioBluetoothCard(QObject *parent)
    : DAudioCard (parent)
{

}

QString DAudioBluetoothCard::mode() const
{
    return QString();
}

QStringList DAudioBluetoothCard::modeOptions() const
{
    return {};
}

void DAudioBluetoothCard::setMode(QString mode)
{

}
DAUDIOMANAGER_END_NAMESPACE
