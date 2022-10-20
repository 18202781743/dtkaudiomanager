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
    virtual bool exec() = 0;
    QStringList m_argus;
    DAudioManager m_handler;
};

class CommandManager
{
public:
    using CommandCreator = std::function<Command *()>;
    ~CommandManager()
    {
        m_commands.clear();
    }
    void regist(const QString &cmd, const QString &desc, const CommandCreator &creator)
    {
        m_commands.insert(cmd, creator);
        m_descs.insert(cmd, desc);
    }
    bool exec(const QStringList &argument)
    {
        do {
            if (argument.size() <= 1) {
                break;
            }

            auto cmd = argument[1];
            if (cmd == "all") {
                return execAllCommand();
            }

            if (!m_commands.contains(cmd)) {
                break;
            }

            if (auto creator = m_commands.value(cmd)) {
                auto command = creator();
                command->m_argus = argument.mid(1);
                qInfo() << m_descs.value(cmd);
                return command->exec();
            }

        } while(false);

        return outputHelp();
    }
    bool outputHelp()
    {
        for (auto iter = m_descs.begin(); iter != m_descs.end(); ++iter) {
            qInfo() << iter.key() << "    " << iter.value();
        }
        return true;
    }
    bool execAllCommand()
    {
        bool exit = true;
        for (auto iter = m_commands.begin(); iter != m_commands.end(); ++iter) {
            auto creator = iter.value();
            auto command = creator();
            qInfo() << m_descs.value(iter.key());
            exit &= command->exec();
        }
        return exit;
    }
    QMap<QString, CommandCreator> m_commands;
    QMap<QString, QString> m_descs;
};

struct ListCards : public Command
{
    virtual bool exec()
    {
        auto cards = m_handler.cards();
        qInfo() << "card info:";
        for (auto card : cards) {
            qInfo() << card->name();
            qInfo() << "\t" << "port info:";
            for (auto port : card->ports()) {
                qInfo() << "\t" << port->name() << port->description();
            }
        }
        return true;
    }
};

struct ListInputDevices : public Command
{
    virtual bool exec()
    {
        qInfo() << "input devices info:";
        for (auto inputDevice : m_handler.inputDevices()) {
            qInfo() << inputDevice->name();
        }
        return true;
    }
};

struct MonitorCards : public Command
{
    virtual bool exec()
    {
        m_cards = m_handler.cards();
        print(m_cards);
        QObject::connect(&m_handler, &DAudioManager::cardsChanged, [this]() {
            m_cards = m_handler.cards();
            print(m_cards);
        });
        return false;
    }
    void print(const QList<DAudioCardPtr> &cards)
    {
        qInfo() << "card info:";
        for (auto item : cards) {
            qInfo() << item->name();
        }
    }
    QList<DAudioCardPtr> m_cards;
};

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    CommandManager manager;
    manager.regist("list-cards", "List cards", [](){ return new ListCards;});
    manager.regist("list-input-devices", "List loaded input devices", [](){ return new ListInputDevices;});
    manager.regist("monitor-cards", "Monitor cards changed", [](){ return new MonitorCards;});
    QTimer::singleShot(0, qApp, [&manager, &app]() {
        if (manager.exec(app.arguments())) {
            app.exit(0);
        }
    });

    return app.exec();
}
