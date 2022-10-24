// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "dtkaudiomanager_global.h"
#include "daudioport.h"

#include <QObject>

DAUDIOMANAGER_BEGIN_NAMESPACE
class DAudioPort;
class DPlatformAudioCard;
class LIBDTKAUDIOMANAGERSHARED_EXPORT DPlatformAudioPort : public QObject, public QSharedData
{
    Q_OBJECT

public:
    explicit DPlatformAudioPort(DPlatformAudioCard *card);
    virtual ~DPlatformAudioPort();
    virtual bool isEnabled() const;
    virtual void setEnabled(const bool enabled);

    virtual bool isActive() const;
    virtual void setActive(const int active);
    int direction() const;
    void setDirection(const int direction);
    QString name() const;
    void setName(const QString &name);
    QString description() const;
    void setDescription(const QString &description);
    virtual DAudioPort *create()
    {
        return new DAudioPort(this);
    }

Q_SIGNALS:

    void nameChanged(QString name);
    void descriptionChanged(QString description);
    void enabledChanged(bool enabled);

protected:
    DPlatformAudioCard *m_card = nullptr;
    int m_direction = 1;
    bool m_isActive = false;
    bool m_isEnabled = false;
    QString m_name;
    QString m_description;
};
DAUDIOMANAGER_END_NAMESPACE
