// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "daudioport.h"
#include "daudiocard.h"
#include "daudioport_p.h"

#include <QObject>

DAUDIOMANAGER_BEGIN_NAMESPACE
class DPlatformAudioPort;
class DAudioPort;
class DAudioCard;
class LIBDTKAUDIOMANAGERSHARED_EXPORT DPlatformAudioCard : public QObject, public QSharedData
{
    Q_OBJECT

public:
    explicit DPlatformAudioCard(QObject *parent = nullptr);
    virtual ~DPlatformAudioCard();

    virtual quint32 index() const;
    QString name() const;
    void setName(const QString &name);

    bool enabled() const;
    void setEnabled(const bool enabled);

    void addPort(DPlatformAudioPort *port);
    DPlatformAudioPort *portByName(const QString &portName) const;
    virtual DAudioCard *create()
    {
        return new DAudioCard(this);
    }

Q_SIGNALS:
    void enabledChanged(bool enabled);

public:
    QList<QExplicitlySharedDataPointer<DPlatformAudioPort>> m_ports;
    QString m_name;
    bool m_enabled;
};

class LIBDTKAUDIOMANAGERSHARED_EXPORT DPlatformAudioBluetoothCard : public DPlatformAudioCard
{
    Q_OBJECT

public:
    virtual DAudioCard *create() override
    {
        return new DAudioBluetoothCard(this);
    }

    virtual QString mode() const = 0;
    virtual QStringList modeOptions() const = 0;

public Q_SLOTS:
    virtual void setMode(const QString &mode) = 0;

Q_SIGNALS:
    void modeChanged(const QString &mode);

    void modeOptionsChanged(const QStringList &modeOptions);

};
DAUDIOMANAGER_END_NAMESPACE
