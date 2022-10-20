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
    virtual ~DPlatformAudioCard();

    virtual quint32 index() const;
    virtual QString name() const = 0;

    virtual bool enabled() const = 0;

    void addPort(DPlatformAudioPort *port);
    virtual DAudioCard *create()
    {
        return new DAudioCard(this);
    }

Q_SIGNALS:
    void enabledChanged(bool enabled);

public:
    QList<QExplicitlySharedDataPointer<DPlatformAudioPort>> m_ports;
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
    virtual void setMode(QString mode) = 0;

Q_SIGNALS:
    void modeChanged(QString mode);

    void modeOptionsChanged(QStringList modeOptions);

};
DAUDIOMANAGER_END_NAMESPACE
