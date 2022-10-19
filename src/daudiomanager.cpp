// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "daudiomanager.h"
#include "daudiomanager_p.h"
#include "daudiofactory_p.h"

#include <QDebug>

DAUDIOMANAGER_BEGIN_NAMESPACE

DAudioManager::DAudioManager(QObject *parent)
    : DAudioManager(DAudioFactory::createAudioManager(), parent)
{
}

DAudioManager::DAudioManager(DAudioManagerPrivate *d, QObject *parent)
    : QObject(parent)
    , d(d)
{
    Q_ASSERT(this->d);
    connect(this->d.data(), &DAudioManagerPrivate::cardsChanged, this, &DAudioManager::cardsChanged);
}

DAudioManager::~DAudioManager()
{
    d->m_cards.clear();

    qDeleteAll(d->m_inputDevices);
    d->m_inputDevices.clear();

    qDeleteAll(d->m_outputDevices);
    d->m_outputDevices.clear();

    qDeleteAll(d->m_inputStreams);
    d->m_inputStreams.clear();

    qDeleteAll(d->m_outputStreams);
    d->m_outputStreams.clear();
}

QList<DAudioCardPtr> DAudioManager::cards() const
{
    QList<DAudioCardPtr> result;
    for (auto item : d->m_cards) {
        result << DAudioCardPtr(item->create());
    }
    return result;
}

DAudioCardPtr DAudioManager::card(const QString &cardName) const
{
    for (auto item : d->m_cards) {
        if (item->name() == cardName)
            return DAudioCardPtr(item->create());
    }
    return nullptr;
}

QList<DAudioCardPtr> DAudioManager::availableCards() const
{
    QList<DAudioCardPtr> result;
    for (auto item : d->m_cards) {
        if (item->enabled()) {
            result << DAudioCardPtr(item->create());
        }
    }
    return result;
}

QList<DAudioInputDevicePtr> DAudioManager::inputDevices() const
{
    QList<DAudioInputDevicePtr> result;
    for (auto item : d->m_inputDevices) {
        result << DAudioInputDevicePtr(item->create());
    }
    return result;
}

QList<DAudioOutputDevicePtr> DAudioManager::outputDevices() const
{
    QList<DAudioOutputDevicePtr> result;
    for (auto item : d->m_outputDevices) {
        result << DAudioOutputDevicePtr(item->create());
    }
    return result;
}

DAudioInputDevicePtr DAudioManager::defaultInputDevice() const
{
    for (auto item : d->m_inputDevices) {
        if (item->mute())
            return DAudioInputDevicePtr(item->create());
    }
    return nullptr;
}

DAudioOutputDevicePtr DAudioManager::defaultOutputDevice() const
{
    for (auto item : d->m_outputDevices) {
        if (item->mute())
            return DAudioOutputDevicePtr(item->create());
    }
    return nullptr;
}

QList<DAudioInputDevicePtr> DAudioManager::availableInputDevices() const
{
    QList<DAudioInputDevicePtr> result;
    for (auto item : d->m_inputDevices) {
        if (item->mute()) {
            result << DAudioInputDevicePtr(item->create());
        }
    }
    return result;
}

QList<DAudioOutputDevicePtr> DAudioManager::availableOutputDevices() const
{
    QList<DAudioOutputDevicePtr> result;
    for (auto item : d->m_outputDevices) {
        if (item->mute()) {
            result << DAudioOutputDevicePtr(item->create());
        }
    }
    return result;
}

DAudioInputDevicePtr DAudioManager::inputDevice(const QString &deviceName) const
{
    for (auto item : d->m_inputDevices) {
        if (item->name() == deviceName)
            return DAudioInputDevicePtr(item->create());
    }
    return nullptr;
}

DAudioOutputDevicePtr DAudioManager::outputDevice(const QString &deviceName) const
{
    for (auto item : d->m_outputDevices) {
        if (item->name() == deviceName)
            return DAudioOutputDevicePtr(item->create());
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

double DAudioManager::maxVolume() const
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
