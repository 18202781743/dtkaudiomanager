// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "daudioport_p.h"
#include "dbus/ddbusinterface.h"

#include <QObject>

DAUDIOMANAGER_BEGIN_NAMESPACE
class DDaemonAudioPort : public DPlatformAudioPort
{
    Q_OBJECT

public:
    explicit DDaemonAudioPort(DPlatformAudioCard *card);
    virtual ~DDaemonAudioPort() override;

    void setEnabled(const bool enabled) override;
    bool isEnabled() const override;

    int direction() const override;
    QString name() const override;
    QString description() const override;

public:
    QString m_name;
    QString m_description;
private:
    DDBusInterface *m_inter = nullptr;
};
DAUDIOMANAGER_END_NAMESPACE
