// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "daudiofactory_p.h"
#include "daudioplugin_p.h"

#include <QDebug>
#include <QCoreApplication>
#include <QDir>
#include <QObject>
#include <QPluginLoader>

DAUDIOMANAGER_BEGIN_NAMESPACE

class DAudioPluginLoader
{
public:
    void loadMetas()
    {
        for (QString fileName : pluginPaths()) {
            const auto &info = parsePluginInfo(fileName);
            if (!info.isEmpty()) {
                m_metas.insert(info, fileName);
                qDebug() << "load the plugin [" << info << "] successful." << fileName;
            }
        }
    }

    QStringList keys() const
    {
        return m_metas.keys();
    }

    DAudioPlugin *plugin()
    {
        if (m_plugin)
            return m_plugin;

        for (auto key : keys()) {
            auto fileName = m_metas.value(key);

            QPluginLoader loader(fileName);
            if (!loader.instance()) {
                qWarning() << "load the plugin error." << loader.errorString();
                break;
            }
            m_plugin = qobject_cast<DAudioPlugin *>(loader.instance());
            if (!m_plugin) {
                qWarning() << "the plugin isn't a IWidgetPlugin." << fileName;
                break;
            }
        }
        return m_plugin;

    }

private:
    QStringList pluginPaths() const
    {
        // The same pluginid will be overwritten by later, `DTK_AUDIO_PLUGIN_DIRS` > `./plugins` > `/usr`
        QStringList dirs;
        dirs << "/usr/lib/dtk/plugins";
        dirs << QCoreApplication::applicationDirPath() + "/plugins";
        const QString &envPaths = qEnvironmentVariable("DTK_AUDIO_PLUGIN_DIRS");
        if (!envPaths.isEmpty()) {
            QStringList list = envPaths.split(':');
            std::reverse(list.begin(), list.end());
            dirs << list;
        }

        qDebug() << "load plugins from those dir:" << dirs;
        QStringList pluginPaths;
        for (auto dir : qAsConst(dirs)) {
            auto pluginsDir = QDir(dir);
            if (!pluginsDir.exists())
                continue;

            const auto entryList = pluginsDir.entryList(QDir::Files);
            for (const QString &fileName : qAsConst(entryList)) {
                const auto path = pluginsDir.absoluteFilePath(fileName);
                if (!QLibrary::isLibrary(path))
                    continue;

                if (!isPlugin(path))
                    continue;

                pluginPaths << path;
            }
        }
        return pluginPaths;
    }

    bool isPlugin(const QString &fileName) const
    {
        const auto &info = parsePluginInfo(fileName);
        return !info.isEmpty();
    }

    QString parsePluginInfo(const QString &fileName) const
    {
        QPluginLoader loader(fileName);
        const auto &meta = loader.metaData();

        do {
            const auto iid = meta["IID"].toString();
            if (iid.isEmpty())
                break;

            if (iid != QString(qobject_interface_iid<DAudioPlugin *>()))
                break;

            const auto key = meta["Key"].toString();
            if (key.isEmpty())
                break;

            return fileName;
        } while (false);

        return QString();
    }

private:
    QMap<QString, QString> m_metas;
    DAudioPlugin *m_plugin = nullptr;
};


Q_GLOBAL_STATIC(DAudioPluginLoader, loader)

DAudioManagerPrivate *DAudioFactory::createAudioManager()
{
    auto plugin = loader->plugin();
    return plugin ? plugin->createAudioManager() : nullptr;
}

DAUDIOMANAGER_END_NAMESPACE
