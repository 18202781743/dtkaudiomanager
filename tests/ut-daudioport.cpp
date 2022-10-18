// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "gtest/gtest.h"

#include "daudioport.h"
#include "daudioport_p.h"

#include "ut-daudiohelpers.hpp"

#include <QPointer>

DAUDIOMANAGER_USE_NAMESPACE

class ut_DAudioPort : public testing::Test
{
public:
    void SetUp() override
    {
        m_impl.reset(new TestAudioPort());
        m_target = m_impl->source();
    }
    void TearDown() override;
public:
    QPointer<DAudioPort> m_target;
    QScopedPointer<TestAudioPort> m_impl;
};

void ut_DAudioPort::TearDown() {}

TEST_F(ut_DAudioPort, base)
{
    EXPECT_EQ(TestAudioPortName, m_target->name());
    EXPECT_EQ(TestAudioPortDescription, m_target->description());
    EXPECT_FALSE(m_target->isEnabled());
    m_target->setEnabled(true);
    EXPECT_TRUE(m_target->isEnabled());
    EXPECT_EQ(m_target->direction(), 1);
}
