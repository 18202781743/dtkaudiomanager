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
    virtual void setEnabled(const bool enabled) = 0;
    virtual bool isEnabled() const = 0;

    virtual int direction() const = 0;
    virtual QString name() const = 0;
    virtual QString description() const = 0;
    virtual DAudioPort *create()
    {
        return new DAudioPort(this);
    }

Q_SIGNALS:

    void directionChanged(int direction);
    void nameChanged(QString name);
    void descriptionChanged(QString description);

protected:
    DPlatformAudioCard *m_card = nullptr;

};
DAUDIOMANAGER_END_NAMESPACE
