// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "daudiostream.h"
#include "daudiodevice.h"

#include <QDebug>

DAUDIOMANAGER_BEGIN_NAMESPACE

DAudioStream::DAudioStream(DAudioDevice *parent)
    : QObject (parent)
{

}

DAudioStream::~DAudioStream()
{

}

QString DAudioStream::card() const
{
    return QString();
}

DAudioInputStream::DAudioInputStream(DAudioDevice *parent)
    : DAudioStream (parent)
{

}

DAudioInputStream::~DAudioInputStream()
{

}

bool DAudioInputStream::mute() const
{
    return false;
}

double DAudioInputStream::fade() const
{
    return 0.0;
}

double DAudioInputStream::volume() const
{
    return 0.0;
}

double DAudioInputStream::balance() const
{
    return 0.0;
}

bool DAudioInputStream::supportBalance() const
{
    return false;
}

bool DAudioInputStream::supportFade() const
{
    return false;
}

double DAudioInputStream::meterVolume() const
{
    return 0.0;
}

void DAudioInputStream::setMute(bool mute)
{

}

void DAudioInputStream::setFade(double fade)
{

}

void DAudioInputStream::setVolume(double volume)
{

}

void DAudioInputStream::setBalance(double balance)
{

}

DAudioOutputStream::DAudioOutputStream(DAudioDevice *parent)
    : DAudioStream (parent)
{

}

DAudioOutputStream::~DAudioOutputStream()
{

}

bool DAudioOutputStream::mute() const
{
    return false;
}

double DAudioOutputStream::fade() const
{
    return 0.0;
}

double DAudioOutputStream::volume() const
{
    return 0.0;
}

double DAudioOutputStream::balance() const
{
    return 0.0;
}

bool DAudioOutputStream::supportBalance() const
{
    return false;
}

bool DAudioOutputStream::supportFade() const
{
    return false;
}

double DAudioOutputStream::meterVolume() const
{
    return 0.0;
}

void DAudioOutputStream::setMute(bool mute)
{

}

void DAudioOutputStream::setFade(double fade)
{

}

void DAudioOutputStream::setVolume(double volume)
{

}

void DAudioOutputStream::setBalance(double balance)
{

}
DAUDIOMANAGER_END_NAMESPACE
