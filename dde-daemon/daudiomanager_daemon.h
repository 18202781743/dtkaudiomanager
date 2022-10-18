// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "daudiomanager_p.h"
#include "dbus/ddbusinterface.h"

#include <QObject>

DAUDIOMANAGER_BEGIN_NAMESPACE

class LIBDTKAUDIOMANAGERSHARED_EXPORT DDaemonAudioManager : public DAudioManagerPrivate
{
    Q_OBJECT

public:
    DDaemonAudioManager(QObject *parent = nullptr);
    virtual ~DDaemonAudioManager() override;

    virtual void reset() override;
    virtual void setReConnectionEnabled(const bool enable) override;
    virtual void setPort(const QString& card, const QString &portName, const int direction) override;
    virtual void setPortEnabled(const QString& card, const QString &portName) override;

    virtual bool increaseVolume() const override;
    virtual bool reduceNoise() const override;
    virtual bool maxVolume() const override;
public Q_SLOTS:
    void setIncreaseVolume(bool increaseVolume);
    void setReduceNoise(bool reduceNoise);

Q_SIGNALS:
    void deviceAdded(const QString &name, const bool isInputDevice);
    void deviceRemoved(const QString &name, const bool isInputDevice);

    void increaseVolumeChanged(bool increaseVolume);
    void reduceNoiseChanged(bool reduceNoise);
    void maxVolumeChanged(bool maxVolume);

private:
    void updateCards();
    void updateInputDevice();

private:
    DDBusInterface *m_inter = nullptr;

};
DAUDIOMANAGER_END_NAMESPACE
