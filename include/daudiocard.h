// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "namespace.h"

#include <QObject>

DAUDIOMANAGER_BEGIN_NAMESPACE
class DAudioPort;
class DAudioCardPrivate;
class LIBDTKAUDIOMANAGERSHARED_EXPORT DAudioCard : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool enabled READ enabled NOTIFY enabledChanged)
public:
    explicit DAudioCard(QObject *parent = nullptr);
    virtual ~DAudioCard() override;

    QList<DAudioPort *> ports() const;
    QString name() const;

    bool enabled() const;

Q_SIGNALS:
    void enabledChanged(bool enabled);

private:
    Q_DISABLE_COPY(DAudioCard)
    Q_DECLARE_PRIVATE(DAudioCard)
};

class DAudioBluetoothCardPrivate;
class LIBDTKAUDIOMANAGERSHARED_EXPORT DAudioBluetoothCard : public DAudioCard
{
    Q_OBJECT

    Q_PROPERTY(QString mode READ mode WRITE setMode NOTIFY modeChanged)
    Q_PROPERTY(QStringList modeOptions READ modeOptions NOTIFY modeOptionsChanged)
public:
    explicit DAudioBluetoothCard(QObject *parent = nullptr);

    QString mode() const;
    QStringList modeOptions() const;

public Q_SLOTS:
    void setMode(QString mode);

Q_SIGNALS:
    void modeChanged(QString mode);

    void modeOptionsChanged(QStringList modeOptions);

private:
    Q_DISABLE_COPY(DAudioBluetoothCard)
    Q_DECLARE_PRIVATE(DAudioBluetoothCard)
};
DAUDIOMANAGER_END_NAMESPACE
