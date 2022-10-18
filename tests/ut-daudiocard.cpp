// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "gtest/gtest.h"

#include "daudioport.h"
#include "daudioport_p.h"

#include "daudiocard.h"
#include "daudiocard_p.h"
#include "ut-daudiohelpers.hpp"

#include <QPointer>
#include <QSignalSpy>

DAUDIOMANAGER_USE_NAMESPACE

class ut_DAudioCard : public testing::Test
{
public:
    void SetUp() override
    {
        m_impl.reset(new TestAudioCard());
        m_target = m_impl->source();
    }
    void TearDown() override;
public:
    QPointer<DAudioCard> m_target;
    QScopedPointer<TestAudioCard> m_impl;
};

void ut_DAudioCard::TearDown() {}

TEST_F(ut_DAudioCard, base)
{
    EXPECT_EQ(TestAudioCardName, m_target->name());
    EXPECT_FALSE(m_target->enabled());
    QSignalSpy spy(m_target.data(), &DAudioCard::enabledChanged);
    m_impl->setEnabled(true);
    EXPECT_TRUE(m_target->enabled());
    EXPECT_EQ(spy.count(), 1);
}

TEST_F(ut_DAudioCard, port)
{
    EXPECT_TRUE(m_target->ports().isEmpty());
    QScopedPointer<TestAudioPort> port1(new TestAudioPort(m_impl.data()));
    EXPECT_EQ(m_target->ports().count(), 1);
    auto port = m_target->ports()[0];
    EXPECT_EQ(port->name(), port1->name());
}
