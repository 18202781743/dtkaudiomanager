// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <QDBusInterface>
#include <QObject>

namespace DDaemonInternal {
static const QString AudioServiceName("com.deepin.daemon.Audio");
static const QString AudioServiceInterface(AudioServiceName);
static const QString AudioPath("/com/deepin/daemon/Audio");

inline QDBusInterface *createAudioInterface()
{
    return new QDBusInterface(AudioServiceName, AudioPath, AudioServiceInterface);
}
}
