// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "daudioplugin_daemon.h"

#include "daudiomanager_daemon.h"
#include "daudiocard_daemon.h"
#include "daudioport_daemon.h"

#include <QDebug>

DAUDIOMANAGER_BEGIN_NAMESPACE

DDaemonAudioPlugin::DDaemonAudioPlugin(QObject *parent)
    : DAudioPlugin(parent)
{

}

DAudioManagerPrivate *DDaemonAudioPlugin::createAudioManager()
{
    return new DDaemonAudioManager();
}

QList<DPlatformAudioCard *> DDaemonAudioPlugin::cards()
{
    return {};
}

DPlatformAudioCard *DDaemonAudioPlugin::createPlatformAudioCard()
{
    return new DDaemonAudioCard();
}

DPlatformAudioPort *DDaemonAudioPlugin::createPlatformAudioPort()
{
    return nullptr;
}

DAUDIOMANAGER_END_NAMESPACE
