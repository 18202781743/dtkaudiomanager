// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "daudiocard_daemon.h"
#include "daudioport.h"
#include "daudioport_daemon.h"

#include <QDebug>

DAUDIOMANAGER_BEGIN_NAMESPACE

DDaemonAudioCard::DDaemonAudioCard(QObject *parent)
{
    m_inter = new DDBusInterface("com.deepin.daemon.Audio", "/com/deepin/daemon/Audio");
    if (!m_inter->isValid()) {
        qWarning() << m_inter->lastError();
    }
}

DDaemonAudioCard::~DDaemonAudioCard()
{

}

QList<DAudioPort *> DDaemonAudioCard::ports() const
{
    return { };
}

QString DDaemonAudioCard::name() const
{
    return QString();
}

bool DDaemonAudioCard::enabled() const
{
    return false;
}

DDaemonAudioBluetoothCard::DDaemonAudioBluetoothCard(QObject *parent)
    : DDaemonAudioCard (parent)
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
