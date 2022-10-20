// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "dtkaudiomanager_global.h"
#include "daudiodevice.h"
#include "daudiocard_p.h"
#include "daudiostream.h"
#include "daudiostream_p.h"

#include <QObject>

DAUDIOMANAGER_BEGIN_NAMESPACE
class DAudioCard;
class DAudioDevicePrivate;
class LIBDTKAUDIOMANAGERSHARED_EXPORT DPlatformAudioInputDevice : public QObject, public QSharedData
{
    Q_OBJECT
public:
    explicit DPlatformAudioInputDevice(DPlatformAudioCard *card = nullptr)
        : m_card(card)
    {
    }
    virtual ~DPlatformAudioInputDevice() override
    {
    }
    void setCard(DPlatformAudioCard *card)
    {
        m_card = card;
    }

    virtual DAudioInputDevice *create()
    {
        return new DAudioInputDevice(this);
    }

    QString key() const { return m_key; }
    void setKey(const QString &key) { m_key = key; }

    virtual bool mute() const = 0;
    virtual double fade() const = 0;
    virtual double volume() const = 0;
    virtual double balance() const = 0;

    virtual bool supportBalance() const = 0;
    virtual bool supportFade() const = 0;
    virtual double baseVolume() const = 0;

    virtual double meterVolume() const = 0;

    void addStream(DPlatformAudioOutputStream *stream)
    {
        m_streams.append(stream);
        Q_EMIT streamAdded(stream->name());
    }
    void removeStream(const QString &streamName)
    {
        bool hasChanged = false;
        for (auto item : m_streams) {
            if (item->name() == streamName) {
                m_streams.removeOne(item);
                break;
            }
        }
        if (hasChanged) {
            Q_EMIT streamRemoved(streamName);
        }
    }

    QString name() const
    {
        return m_name;
    }

    QString description() const
    {
        return m_description;
    }

    void setName(const QString &name)
    {
        if (name == m_name)
            return;
        m_name = name;
        Q_EMIT nameChanged(m_name);
    }
    void setDescription(const QString &description)
    {
        if (description == m_description)
            return;
        m_description = description;
        Q_EMIT descriptionChanged(m_description);
    }

public Q_SLOTS:
    virtual void setMute(bool mute) = 0;
    virtual void setFade(double fade) = 0;
    virtual void setVolume(double volume) = 0;
    virtual void setBalance(double balance) = 0;

Q_SIGNALS:
    void streamAdded(const QString &name);
    void streamRemoved(const QString &name);

    void muteChanged(bool mute);
    void fadeChanged(double fade);
    void volumeChanged(double volume);
    void balanceChanged(double balance);

    void supportBalanceChanged(bool supportBalance);
    void supportFadeChanged(bool supportFade);
    void baseVolumeChanged(double baseVolume);

    void meterVolumeChanged(double meterVolume);

    void nameChanged(QString name);
    void descriptionChanged(QString description);

public:
    DPlatformAudioCard *m_card = nullptr;
    QList<DPlatformAudioOutputStream *> m_streams;
    QString m_key;
    QString m_name;
    QString  m_description;
};

class LIBDTKAUDIOMANAGERSHARED_EXPORT DPlatformAudioOutputDevice : public QObject, public QSharedData
{
    Q_OBJECT
public:
    explicit DPlatformAudioOutputDevice(DPlatformAudioCard *card = nullptr)
        : m_card(card)
    {
    }
    virtual ~DPlatformAudioOutputDevice() override
    {
    }
    virtual DAudioOutputDevice *create()
    {
        return new DAudioOutputDevice(this);
    }

    QString key() const { return m_key; }
    void setKey(const QString &key) { m_key = key; }

    virtual bool mute() const = 0;
    virtual double fade() const = 0;
    virtual double volume() const = 0;
    virtual double balance() const = 0;

    virtual bool supportBalance() const = 0;
    virtual bool supportFade() const = 0;
    virtual double baseVolume() const = 0;

    virtual double meterVolume() const = 0;

    void addStream(DPlatformAudioInputStream *stream)
    {
        m_streams.append(QExplicitlySharedDataPointer(stream));
        Q_EMIT streamAdded(stream->name());
    }
    void removeStream(const QString &streamName)
    {
        bool hasChanged = false;
        for (auto item : m_streams) {
            if (item->name() == streamName) {
                m_streams.removeOne(item);
                break;
            }
        }
        if (hasChanged) {
            Q_EMIT streamRemoved(streamName);
        }
    }

    QString name() const
    {
        return m_name;
    }

    QString description() const
    {
        return m_description;
    }

    void setName(const QString &name)
    {
        if (name == m_name)
            return;
        m_name = name;
        Q_EMIT nameChanged(m_name);
    }
    void setDescription(const QString &description)
    {
        if (description == m_description)
            return;
        m_description = description;
        Q_EMIT descriptionChanged(m_description);
    }

public Q_SLOTS:
    virtual void setMute(bool mute) = 0;
    virtual void setFade(double fade) = 0;
    virtual void setVolume(double volume) = 0;
    virtual void setBalance(double balance) = 0;

Q_SIGNALS:
    void streamAdded(const QString &name);
    void streamRemoved(const QString &name);

    void muteChanged(bool mute);
    void fadeChanged(double fade);
    void volumeChanged(double volume);
    void balanceChanged(double balance);

    void supportBalanceChanged(bool supportBalance);
    void supportFadeChanged(bool supportFade);
    void baseVolumeChanged(double baseVolume);

    void meterVolumeChanged(double meterVolume);

    void nameChanged(QString name);
    void descriptionChanged(QString description);

public:
    DPlatformAudioCard *m_card = nullptr;
    QList<QExplicitlySharedDataPointer<DPlatformAudioInputStream>> m_streams;
    QString m_key;
    QString m_name;
    QString  m_description;
};
DAUDIOMANAGER_END_NAMESPACE
