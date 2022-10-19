// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "daudiocard_daemon.h"
#include "daudioport.h"
#include "daudioport_daemon.h"
#include "daemonhelpers.hpp"

#include <QDebug>

DAUDIOMANAGER_BEGIN_NAMESPACE

DDaemonAudioCard::DDaemonAudioCard(QObject *parent)
{
    m_inter = new QDBusInterface(DDaemonInternal::AudioServiceName,
                                 DDaemonInternal::AudioPath,
                                 DDaemonInternal::AudioServiceInterface);
    if (!m_inter->isValid()) {
        qWarning() << m_inter->lastError();
    }
}

DDaemonAudioCard::~DDaemonAudioCard()
{

}

QString DDaemonAudioCard::name() const
{
    return m_name;
}

bool DDaemonAudioCard::enabled() const
{
    return m_enabled;
}

DDaemonAudioBluetoothCard::DDaemonAudioBluetoothCard(QObject *parent)
    : DDaemonAudioCard (parent)
{

}

DDaemonAudioBluetoothCard::~DDaemonAudioBluetoothCard()
{

}

QString DDaemonAudioBluetoothCard::mode() const
{
    return QString();
}

QStringList DDaemonAudioBluetoothCard::modeOptions() const
{
    return {};
}

void DDaemonAudioBluetoothCard::setMode(QString mode)
{

}
DAUDIOMANAGER_END_NAMESPACE
