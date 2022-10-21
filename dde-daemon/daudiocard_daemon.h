// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "daudiocard_p.h"
#include "dbus/ddbusinterface.h"

#include <QDBusInterface>
#include <QObject>

DAUDIOMANAGER_BEGIN_NAMESPACE
class DPlatformAudioPort;
class DDaemonAudioCard : public DPlatformAudioCard
{
    Q_OBJECT

public:
    explicit DDaemonAudioCard(QObject *parent = nullptr);
    virtual ~DDaemonAudioCard() override;

    QString name() const override;

    bool enabled() const override;

public:
    QScopedPointer<QDBusInterface>  m_inter;
    QString m_name;
    bool m_enabled;
};

class DAudioBluetoothCardPrivate;
class DDaemonAudioBluetoothCard : public DDaemonAudioCard
{
    Q_OBJECT

public:
    explicit DDaemonAudioBluetoothCard(QObject *parent);
    virtual ~DDaemonAudioBluetoothCard() override;

    QString mode() const;
    QStringList modeOptions() const;

public Q_SLOTS:
    void setMode(QString mode);
};
DAUDIOMANAGER_END_NAMESPACE
