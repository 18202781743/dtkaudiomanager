// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "daudioport_daemon.h"
#include "daudiocard_daemon.h"
#include "daemonhelpers.hpp"

#include <QDebug>
#include <QDBusAbstractInterface>

DAUDIOMANAGER_BEGIN_NAMESPACE

DDaemonAudioPort::DDaemonAudioPort(DPlatformAudioCard *card)
    :  DPlatformAudioPort (card)
{
    Q_ASSERT(m_card);
}

DDaemonAudioPort::~DDaemonAudioPort()
{

}

void DDaemonAudioPort::setEnabled(const bool enabled)
{
    auto inter = DDaemonInternal::audioInterface();
    inter.call("SetPortEnabled", m_card->name(), m_name, enabled);
}

bool DDaemonAudioPort::isEnabled() const
{
    return false;
}

void DDaemonAudioPort::setActive(const int active)
{
    auto inter = DDaemonInternal::audioInterface();
    inter.call("SetPort", m_card->name(), m_name, m_direction);
    DPlatformAudioPort::setActive(active);
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
