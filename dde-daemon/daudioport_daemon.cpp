// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "daudioport_daemon.h"

#include <QDebug>
#include <QDBusAbstractInterface>

DAUDIOMANAGER_BEGIN_NAMESPACE

DDaemonAudioPort::DDaemonAudioPort(DPlatformAudioCard *card)
    :  DPlatformAudioPort (card)
{
    m_inter = new DDBusInterface("com.deepin.daemon.Audio", "/com/deepin/daemon/Audio");
    if (!m_inter->isValid()) {
        qWarning() << m_inter->lastError();
    }
}

DDaemonAudioPort::~DDaemonAudioPort()
{

}

void DDaemonAudioPort::setEnabled(const bool enabled)
{
    m_inter->call("setPortEnabled", name(), enabled);
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
    return QString();
}

QString DDaemonAudioPort::description() const
{
    return QString();
}


DAUDIOMANAGER_END_NAMESPACE
