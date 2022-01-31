#include "Events.h"
#include "auto_brake.h"
#include <functional>
#define BOOST_TEST_MODULE AutoBrakeTest
#include <boost/test/unit_test.hpp>

struct AutoBrakeTest
{
    MockServiceBus bus{};
    AutoBrake auto_brake{ bus };
};

BOOST_FIXTURE_TEST_CASE(InitialCarSpeedIsZero, AutoBrakeTest)
{
    BOOST_TEST(0 == auto_brake.get_speed_mps());
}

BOOST_FIXTURE_TEST_CASE(InitialSensitivityIsFive, AutoBrakeTest)
{
    BOOST_TEST(5 == auto_brake.get_collision_threshold_s());
}

BOOST_FIXTURE_TEST_CASE(SensitivityGreaterThanOne, AutoBrakeTest)
{  
    BOOST_REQUIRE_THROW(auto_brake.set_collision_threshold_s(0.5L), std::exception);
}

BOOST_FIXTURE_TEST_CASE(SpeedIsSaved, AutoBrakeTest)
{
    bus.speedUpdateCallback(SpeedUpdate{ 100L });
    BOOST_TEST(100 == auto_brake.get_speed_mps());
    bus.speedUpdateCallback(SpeedUpdate{ 50L });
    BOOST_TEST(50 == auto_brake.get_speed_mps());
    bus.speedUpdateCallback(SpeedUpdate{ 0L });
    BOOST_TEST(0 == auto_brake.get_speed_mps());
}

BOOST_FIXTURE_TEST_CASE(NoAlertWhenNotImminent, AutoBrakeTest)
{
    auto_brake.set_collision_threshold_s(2L);
    bus.speedUpdateCallback(SpeedUpdate{ 100L });
    bus.carDetectedCallback(CarDetected{ 1000L, 50L });
    BOOST_TEST(0 == bus.commandsPublished);
}

BOOST_FIXTURE_TEST_CASE(AlertWhenImminent, AutoBrakeTest)
{
    auto_brake.set_collision_threshold_s(10L);
    bus.speedUpdateCallback(SpeedUpdate{ 100L });
    bus.carDetectedCallback(CarDetected{ 100L, 0L });
    BOOST_TEST(1 == bus.commandsPublished);
    BOOST_TEST(1L == bus.lastCommand.time_to_collision_s);
}
