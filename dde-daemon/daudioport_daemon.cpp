// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "daudioport_daemon.h"
#include "daemonhelpers.hpp"

#include <QDebug>
#include <QDBusAbstractInterface>

DAUDIOMANAGER_BEGIN_NAMESPACE

DDaemonAudioPort::DDaemonAudioPort(DPlatformAudioCard *card)
    :  DPlatformAudioPort (card)
{
}

DDaemonAudioPort::~DDaemonAudioPort()
{

}

void DDaemonAudioPort::setEnabled(const bool enabled)
{
//    m_inter->call("setPortEnabled", name(), enabled);
}

bool DDaemonAudioPort::isEnabled() const
{
    return false;
}

int DDaemonAudioPort::direction() const
{
    return 0;
}

QString DDaemonAudioPort::name() const
{
    return m_name;
}

QString DDaemonAudioPort::description() const
{
    return m_description;
}


DAUDIOMANAGER_END_NAMESPACE
