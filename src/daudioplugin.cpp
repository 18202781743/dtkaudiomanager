// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "daudioplugin_p.h"

#include <QObject>

DAUDIOMANAGER_BEGIN_NAMESPACE

DAudioPlugin::DAudioPlugin(QObject *parent)
    : QObject (parent)
{
}

DAudioPlugin::~DAudioPlugin() {}

DAUDIOMANAGER_END_NAMESPACE
