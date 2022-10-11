// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "daudioport.h"

#include <QDebug>

DAUDIOMANAGER_BEGIN_NAMESPACE

DAudioPort::DAudioPort(QObject *parent)
    : QObject (parent)
{

}

DAudioPort::~DAudioPort()
{

}

void DAudioPort::setEnabled(const bool enabled)
{

}

bool DAudioPort::isEnabled() const
{
    return false;
}

int DAudioPort::direction() const
{
    return 0;
}

QString DAudioPort::name() const
{
    return QString();
}

QString DAudioPort::description() const
{
    return QString();
}


DAUDIOMANAGER_END_NAMESPACE
