// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "dtkaudiomanager_global.h"
#include "daudiomanager.h"
#include "daudiocard_p.h"
#include "daudiodevice_p.h"
#include "daudiostream_p.h"

#include <QObject>

DAUDIOMANAGER_BEGIN_NAMESPACE
class DPlatformAudioCard;
class DAudioInputDevice;
class DAudioOutputDevice;

class LIBDTKAUDIOMANAGERSHARED_EXPORT DAudioManagerPrivate : public QObject
{
    Q_OBJECT

public:

    virtual void reset() = 0;
    virtual void setReConnectionEnabled(const bool enable) = 0;
    virtual void setPort(const QString& card, const QString &portName, const int direction) = 0;
    virtual void setPortEnabled(const QString& card, const QString &portName) = 0;

    virtual bool increaseVolume() const = 0;
    virtual bool reduceNoise() const = 0;
    virtual double maxVolume() const = 0;

    void addCard(DPlatformAudioCard *card)
    {
        m_cards.append(QExplicitlySharedDataPointer(card));
        Q_EMIT cardsChanged();
    }
    void removeCard(const QString &cardName)
    {
        bool hasChanged = false;
        for (auto item : m_cards) {
            if (item->name() == cardName) {
                m_cards.removeOne(item);
                break;
            }
        }
        if (hasChanged) {
            Q_EMIT cardsChanged();
        }
    }

public Q_SLOTS:
    virtual void setIncreaseVolume(bool increaseVolume) = 0;
    virtual void setReduceNoise(bool reduceNoise) = 0;

Q_SIGNALS:
    void deviceAdded(const QString &name, const bool isInputDevice);
    void deviceRemoved(const QString &name, const bool isInputDevice);
    void cardsChanged();

    void increaseVolumeChanged(bool increaseVolume);
    void reduceNoiseChanged(bool reduceNoise);
    void maxVolumeChanged(bool maxVolume);

public:
    QList<QExplicitlySharedDataPointer<DPlatformAudioCard>> m_cards;
    QList<DPlatformAudioInputDevice *> m_inputDevices;
    QList<DPlatformAudioOutputDevice *> m_outputDevices;
    QList<DPlatformAudioInputStream *> m_inputStreams;
    QList<DPlatformAudioOutputStream *> m_outputStreams;

};
DAUDIOMANAGER_END_NAMESPACE
