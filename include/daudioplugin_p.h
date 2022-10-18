// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "namespace.h"
#include <QtPlugin>

#include <QObject>

DAUDIOMANAGER_BEGIN_NAMESPACE
class DPlatformAudioPort;
class DPlatformAudioCard;
class DAudioManagerPrivate;
class LIBDTKAUDIOMANAGERSHARED_EXPORT DAudioPlugin : public QObject
{
    Q_OBJECT
public:
    explicit DAudioPlugin(QObject *parent = nullptr);
    virtual ~DAudioPlugin();

    virtual DAudioManagerPrivate *createAudioManager() = 0;
    virtual QList<DPlatformAudioCard *> cards() = 0;
    virtual DPlatformAudioCard *createPlatformAudioCard() = 0;
    virtual DPlatformAudioPort *createPlatformAudioPort() = 0;
};
DAUDIOMANAGER_END_NAMESPACE

#define DdeAudioPlugin_iid "org.deepin.dtk.audio.PluginInterface"

Q_DECLARE_INTERFACE(DAUDIOMANAGER_NAMESPACE::DAudioPlugin, DdeAudioPlugin_iid)
