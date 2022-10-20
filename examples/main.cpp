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
    virtual ~Command();
    virtual bool exec() = 0;
    QStringList m_argus;
    DAudioManager m_handler;
};
Command::~Command() {}

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

            m_argus = argument.mid(1);
            bool exit = true;
            if (execCommands(cmd, exit)){
                return exit;
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
    bool execCommands(const QString &cmdPrefix, bool &exit)
    {
        bool existCommand = false;
        for (auto iter = m_commands.begin(); iter != m_commands.end(); ++iter) {
            const auto cmd = iter.key();
            if (cmd == cmdPrefix || cmd.startsWith(cmdPrefix) || cmdPrefix == "all") {
                existCommand = true;

                auto creator = iter.value();
                auto command = creator();
                command->m_argus = m_argus;
                qInfo() << "************" << m_descs.value(iter.key());
                exit &= command->exec();
            }
        }
        return existCommand;
    }
    QMap<QString, CommandCreator> m_commands;
    QMap<QString, QString> m_descs;
    QStringList m_argus;
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
        for (auto device : m_handler.inputDevices()) {
            qInfo() << device->name();
            qInfo() << device->streams().size() << " output streams info:";
            for (auto stream : device->streams()) {
                qInfo() << stream->name();
            }
        }
        return true;
    }
};

struct ListOutputDevices : public Command
{
    virtual bool exec()
    {
        qInfo() << "output devices info:";
        for (auto device : m_handler.outputDevices()) {
            qInfo() << device->name();
            qInfo() << device->streams().size() << " input streams info:";
            for (auto stream : device->streams()) {
                qInfo() << stream->name();
            }
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
    manager.regist("list-output-devices", "List loaded output devices", [](){ return new ListOutputDevices;});
    manager.regist("monitor-cards", "Monitor cards changed", [](){ return new MonitorCards;});
    QTimer::singleShot(0, qApp, [&manager, &app]() {
        if (manager.exec(app.arguments())) {
            app.exit(0);
        }
    });

    return app.exec();
}
