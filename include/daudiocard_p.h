// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "daudioport.h"
#include "daudiocard.h"

#include <QObject>

DAUDIOMANAGER_BEGIN_NAMESPACE
class DPlatformAudioPort;
class DAudioPort;
class DAudioCard;
class LIBDTKAUDIOMANAGERSHARED_EXPORT DPlatformAudioCard : public QObject, public QSharedData
{
    Q_OBJECT

public:
    virtual ~DPlatformAudioCard()
    {
    }

    virtual quint32 index() const { return 0; }
    virtual QString name() const = 0;

    virtual bool enabled() const = 0;

    void addPort(DPlatformAudioPort *port)
    {
        m_ports << port;
    }
    virtual DAudioCard *create()
    {
        return new DAudioCard(this);
    }

    QList<DPlatformAudioPort *> ports() const
    {
        return m_ports;
    }

Q_SIGNALS:
    void enabledChanged(bool enabled);

public:
    QList<DPlatformAudioPort*> m_ports;
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
