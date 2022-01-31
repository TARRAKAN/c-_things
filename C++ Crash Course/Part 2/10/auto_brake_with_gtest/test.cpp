#include "Events.h"
#include "auto_brake.h"
#include <functional>
#include <gtest/gtest.h>

struct AutoBrakeTest : ::testing::Test
{
    MockServiceBus bus{};
    AutoBrake auto_brake { bus };
};

TEST_F(AutoBrakeTest, InitialCarSpeedIsZero)
{
    ASSERT_DOUBLE_EQ(0, auto_brake.get_speed_mps());
}

TEST_F(AutoBrakeTest, InitialSensitivityIsFive)
{
    ASSERT_DOUBLE_EQ(5, auto_brake.get_collision_threshold_s());
}

TEST_F(AutoBrakeTest, SensitivityGreaterThanOne)
{
    ASSERT_ANY_THROW(auto_brake.set_collision_threshold_s(0.5L));
}

TEST_F(AutoBrakeTest, SpeedIsSaved)
{
    bus.speedUpdateCallback(SpeedUpdate{ 100L });
    ASSERT_EQ(100, auto_brake.get_speed_mps());
    bus.speedUpdateCallback(SpeedUpdate{ 50L });
    ASSERT_EQ(50, auto_brake.get_speed_mps());
    bus.speedUpdateCallback(SpeedUpdate{ 0L });
    ASSERT_DOUBLE_EQ(0, auto_brake.get_speed_mps());
}

TEST_F(AutoBrakeTest, NoAlertWhenNotImminent)
{
    auto_brake.set_collision_threshold_s(2L);
    bus.speedUpdateCallback(SpeedUpdate{ 100L });
    bus.carDetectedCallback(CarDetected{ 1000L, 50L });
    ASSERT_EQ(0, bus.commandsPublished);
}

TEST_F(AutoBrakeTest, AlertWhenImminent) {
    auto_brake.set_collision_threshold_s(10L);
    bus.speedUpdateCallback(SpeedUpdate{ 100L });
    bus.carDetectedCallback(CarDetected{ 100L, 0L });
    ASSERT_EQ(1, bus.commandsPublished);
    ASSERT_DOUBLE_EQ(1L, bus.lastCommand.time_to_collision_s);
}
