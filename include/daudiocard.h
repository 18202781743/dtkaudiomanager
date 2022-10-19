// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "dtkaudiomanager_global.h"

#include <QObject>
#include <QSharedPointer>

DAUDIOMANAGER_BEGIN_NAMESPACE
class DAudioPort;
class DPlatformAudioCard;
class LIBDTKAUDIOMANAGERSHARED_EXPORT DAudioCard : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool enabled READ enabled NOTIFY enabledChanged)
public:
    explicit DAudioCard(DPlatformAudioCard *d);
    virtual ~DAudioCard() override;

    QList<QSharedPointer<DAudioPort>> ports() const;
    QString name() const;

    bool enabled() const;

Q_SIGNALS:
    void enabledChanged(bool enabled);

protected:
    Q_DISABLE_COPY(DAudioCard)
    friend class DPlatformAudioCard;
    QExplicitlySharedDataPointer<DPlatformAudioCard> d;
};

class DPlatformAudioBluetoothCard;
class LIBDTKAUDIOMANAGERSHARED_EXPORT DAudioBluetoothCard : public DAudioCard
{
    Q_OBJECT

    Q_PROPERTY(QString mode READ mode WRITE setMode NOTIFY modeChanged)
    Q_PROPERTY(QStringList modeOptions READ modeOptions NOTIFY modeOptionsChanged)
public:

    QString mode() const;
    QStringList modeOptions() const;

public Q_SLOTS:
    void setMode(QString mode);

Q_SIGNALS:
    void modeChanged(QString mode);

    void modeOptionsChanged(QStringList modeOptions);

private:
    friend class DPlatformAudioBluetoothCard;
    DAudioBluetoothCard(DPlatformAudioBluetoothCard *d);
};
DAUDIOMANAGER_END_NAMESPACE
