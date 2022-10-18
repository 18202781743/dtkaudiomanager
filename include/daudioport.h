// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "dtkaudiomanager_global.h"

#include <QObject>

DAUDIOMANAGER_BEGIN_NAMESPACE
class DPlatformAudioPort;
class LIBDTKAUDIOMANAGERSHARED_EXPORT DAudioPort : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int direction READ direction NOTIFY directionChanged)
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(QString description READ description NOTIFY descriptionChanged)

public:
    explicit DAudioPort(DPlatformAudioPort *d);
    virtual ~DAudioPort() override;

    void setEnabled(const bool enabled);
    bool isEnabled() const;

    int direction() const;
    QString name() const;
    QString description() const;

Q_SIGNALS:

    void directionChanged(int direction);
    void nameChanged(QString name);
    void descriptionChanged(QString description);

private:
    Q_DISABLE_COPY(DAudioPort)
    friend class DPlatformAudioPort;
    DPlatformAudioPort *d = nullptr;
};
DAUDIOMANAGER_END_NAMESPACE
