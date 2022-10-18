// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "daudiomanager.h"
#include "daudiomanager_p.h"
#include "daudiofactory_p.h"

#include <QDebug>

DAUDIOMANAGER_BEGIN_NAMESPACE

DAudioManager::DAudioManager(QObject *parent)
    : QObject (parent)
{
    d = DAudioFactory::createAudioManager();
}

DAudioManager::~DAudioManager()
{

}

QList<DAudioCard *> DAudioManager::cards() const
{
    QList<DAudioCard *> result;
    for (auto item : d->m_cards) {
        result << item->source();
    }
    return result;
}

QList<DAudioCard *> DAudioManager::availableCards() const
{
    QList<DAudioCard *> result;
    for (auto item : d->m_cards) {
        if (item->enabled()) {
            result << item->source();
        }
    }
    return result;
}

QList<DAudioInputDevice *> DAudioManager::inputDevices() const
{
    QList<DAudioInputDevice *> result;
    for (auto item : d->m_inputDevices) {
        result << item->source();
    }
    return result;
}

QList<DAudioOutputDevice *> DAudioManager::outputDevices() const
{
    QList<DAudioOutputDevice *> result;
    for (auto item : d->m_outputDevices) {
        result << item->source();
    }
    return result;
}

DAudioInputDevice *DAudioManager::defaultInputDevice() const
{
    for (auto item : d->m_inputDevices) {
        if (item->mute())
            return item->source();
    }
    return nullptr;
}

DAudioOutputDevice *DAudioManager::defaultOutputDevice() const
{
    for (auto item : d->m_outputDevices) {
        if (item->mute())
            return item->source();
    }
    return nullptr;
}

QList<DAudioInputDevice *> DAudioManager::availableInputDevices() const
{
    QList<DAudioInputDevice *> result;
    for (auto item : d->m_inputDevices) {
        if (item->mute()) {
            result << item->source();
        }
    }
    return result;
}

QList<DAudioOutputDevice *> DAudioManager::availableOutputDevices() const
{
    QList<DAudioOutputDevice *> result;
    for (auto item : d->m_outputDevices) {
        if (item->mute()) {
            result << item->source();
        }
    }
    return result;
}

DAudioInputDevice *DAudioManager::inputDevice(const QString &deviceName) const
{
    for (auto item : d->m_inputDevices) {
        if (item->name() == deviceName)
            return item->source();
    }
    return nullptr;
}

DAudioOutputDevice *DAudioManager::outputDevice(const QString &deviceName) const
{
    for (auto item : d->m_outputDevices) {
        if (item->name() == deviceName)
            return item->source();
    }
    return nullptr;
}

void DAudioManager::reset()
{
    d->reset();
}

void DAudioManager::setReConnectionEnabled(const bool enable)
{
    d->setReConnectionEnabled(enable);
}

void DAudioManager::setPort(const QString &card, const QString &portName, const int direction)
{
    d->setPort(card, portName, direction);
}

void DAudioManager::setPortEnabled(const QString &card, const QString &portName)
{
    d->setPortEnabled(card, portName);
}

bool DAudioManager::increaseVolume() const
{
    return d->increaseVolume();
}

bool DAudioManager::reduceNoise() const
{
    return d->reduceNoise();
}

bool DAudioManager::maxVolume() const
{
    return d->maxVolume();
}

void DAudioManager::setIncreaseVolume(bool increaseVolume)
{
    d->setIncreaseVolume(increaseVolume);
}

void DAudioManager::setReduceNoise(bool reduceNoise)
{
    d->setReduceNoise(reduceNoise);
}
DAUDIOMANAGER_END_NAMESPACE
