// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <QCoreApplication>

#include "daudiomanager.h"
#include "daudiocard.h"
#include "daudioport.h"
#include "daudiodevice.h"
#include "daudiostream.h"

#include <QDebug>
#include <QTime>
#include <QTimer>

DAUDIOMANAGER_USE_NAMESPACE

struct Command
{
    virtual ~Command() {}
    virtual void exec() = 0;
    int m_indent;
};

class CommandManager
{
public:
    ~CommandManager()
    {
        qDeleteAll(m_commands);
        m_commands.clear();
    }
    void regist(const QString &cmd, const QString &desc, Command *command)
    {
        m_commands.insert(cmd, command);
        m_descs.insert(cmd, desc);
    }
    void exec(const QStringList &argument)
    {
        do {
            if (argument.size() <= 1) {
                break;
            }

            auto cmd = argument[1];
            if (!m_commands.contains(cmd)) {
                break;
            }
            if (auto command = m_commands.value(cmd)) {
                command->exec();
                return;
            }

        } while(false);

        outputHelp();
    }
    void outputHelp()
    {
        for (auto iter = m_descs.begin(); iter != m_descs.end(); ++iter) {
            qDebug() << iter.key() << "    " << iter.value();
        }
    }
    QMap<QString, Command *> m_commands;
    QMap<QString, QString> m_descs;
};

struct ListCards : public Command
{
    virtual void exec()
    {
        DAudioManager m_handler;
        auto cards = m_handler.cards();
        qInfo() << "card info:";
        for (auto card : cards) {
            qInfo() << card->name();
            qInfo() << "\t" << "port info:";
            for (auto port : card->ports()) {
                qInfo() << "\t" << port->name() << port->description();
            }
        }
    }
};

struct ListInputDevices : public Command
{
    virtual void exec()
    {
        DAudioManager m_handler;
        qInfo() << "input devices info:";
        for (auto inputDevice : m_handler.inputDevices()) {
            qInfo() << inputDevice->name();
        }
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    CommandManager manager;
    manager.regist("list-cards", "List cards", new ListCards());
    manager.regist("list-input-devices", "List loaded input devices", new ListInputDevices());
    QTimer::singleShot(0, qApp, [&manager, &app]() {
        manager.exec(app.arguments());
    });

    return app.exec();
}
