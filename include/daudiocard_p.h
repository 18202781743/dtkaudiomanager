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
class LIBDTKAUDIOMANAGERSHARED_EXPORT DPlatformAudioCard : public QObject
{
    Q_OBJECT

public:
    virtual ~DPlatformAudioCard()
    {
        if  (m_source) {
            m_source->deleteLater();
            m_source = nullptr;
        }
    }

    virtual quint32 index() const { return 0; }
    virtual QString name() const = 0;

    virtual bool enabled() const = 0;

    void addPort(DPlatformAudioPort *port)
    {
        m_ports << port;
    }
    virtual DAudioCard *source()
    {
        if (!m_source) {
            m_source = new DAudioCard(this);
        }
        return m_source;
    }

    QList<DPlatformAudioPort *> ports() const
    {
        return m_ports;
    }

Q_SIGNALS:
    void enabledChanged(bool enabled);

public:
    DAudioCard *m_source = nullptr;
    QList<DPlatformAudioPort*> m_ports;
};

class LIBDTKAUDIOMANAGERSHARED_EXPORT DPlatformAudioBluetoothCard : public DPlatformAudioCard
{
    Q_OBJECT

public:
    virtual DAudioCard *source() override
    {
        if (!m_source) {
            m_source = new DAudioBluetoothCard(this);
        }
        return m_source;
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
