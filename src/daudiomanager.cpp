// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "daudiomanager.h"

#include <QDebug>

DAUDIOMANAGER_BEGIN_NAMESPACE


DAudioManager::DAudioManager(QObject *parent)
    : QObject (parent)
{

}

DAudioManager::~DAudioManager()
{

}

QList<DAudioCard *> DAudioManager::cards() const
{
    return {};
}

QList<DAudioCard *> DAudioManager::availableCards() const
{
    return {};
}

QList<DAudioInputDevice *> DAudioManager::inputDevices() const
{
    return {};
}

QList<DAudioOutputDevice *> DAudioManager::outputDevices() const
{
    return {};
}

DAudioInputDevice *DAudioManager::defaultInputDevice() const
{
    return nullptr;
}

DAudioOutputDevice *DAudioManager::defaultOutputDevice() const
{
    return nullptr;
}

QList<DAudioInputDevice *> DAudioManager::availableInputDevices() const
{
    return {};
}

QList<DAudioOutputDevice *> DAudioManager::availableOutputDevices() const
{
    return {};
}

DAudioInputDevice *DAudioManager::inputDevice(const QString &deviceName) const
{
    return nullptr;
}

DAudioOutputDevice *DAudioManager::outputDevice(const QString &deviceName) const
{
    return nullptr;
}

void DAudioManager::reset()
{

}

void DAudioManager::setReConnectionEnabled(const bool enable)
{

}

void DAudioManager::setPort(const QString &card, const QString &portName, const int direction)
{

}

void DAudioManager::setPortEnabled(const QString &card, const QString &portName)
{

}

bool DAudioManager::increaseVolume() const
{
    return false;
}

bool DAudioManager::reduceNoise() const
{
    return false;
}

bool DAudioManager::maxVolume() const
{
    return false;
}

void DAudioManager::setIncreaseVolume(bool increaseVolume)
{

}

void DAudioManager::setReduceNoise(bool reduceNoise)
{

}



DAUDIOMANAGER_END_NAMESPACE
