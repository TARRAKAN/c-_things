#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Events.h"
#include "auto_brake.h"

TEST_CASE("AutoBrake")
{
    MockServiceBus bus{};
    AutoBrake auto_brake{bus};
    
    SECTION("initializes speed to zero")
    {
        REQUIRE(auto_brake.get_speed_mps() == 0);
    }
    
    SECTION("initializes sensitivity to five")
    {
        REQUIRE(auto_brake.get_collision_threshold_s() == Approx(5L));
    }
    
    SECTION("throws when sensitivity less than one")
    {
        REQUIRE_THROWS(auto_brake.set_collision_threshold_s(0.5L));
    }
    
    SECTION("saves speed after update")
    {
        bus.speedUpdateCallback(SpeedUpdate{100L});
        REQUIRE(100L == auto_brake.get_speed_mps());
        bus.speedUpdateCallback(SpeedUpdate{50L});
        REQUIRE(50L == auto_brake.get_speed_mps());
        bus.speedUpdateCallback(SpeedUpdate{0L});
        REQUIRE(0L == auto_brake.get_speed_mps());
    }
    
    SECTION("no alert when not imminent")
    {
        bus.speedLimitCallback(SpeedLimitDetected{1000});
        auto_brake.set_collision_threshold_s(2L);
        bus.speedUpdateCallback(SpeedUpdate{100L});
        bus.carDetectedCallback(CarDetected{1000L, 50L});
        REQUIRE(bus.commandsPublished == 0);
    }
    
    SECTION("alert when imminent")
    {
        bus.speedLimitCallback(SpeedLimitDetected{1000});
        auto_brake.set_collision_threshold_s(10L);
        bus.speedUpdateCallback(SpeedUpdate{100L});
        bus.carDetectedCallback(CarDetected{100L, 0L});
        REQUIRE(bus.commandsPublished == 1);
        REQUIRE(bus.lastCommand.time_to_collision_s == Approx(1));
    }
    
    SECTION("Last speed limit is 39mps")
    {
        REQUIRE(auto_brake.getSpeedLimit() == 39);
    }
    
    SECTION("saves speed limit after update")
    {
        bus.speedLimitCallback(SpeedLimitDetected{100});
        REQUIRE(100 == auto_brake.getSpeedLimit());
        bus.speedLimitCallback(SpeedLimitDetected{50});
        REQUIRE(50 == auto_brake.getSpeedLimit());
        bus.speedLimitCallback(SpeedLimitDetected{0});
        REQUIRE(0 == auto_brake.getSpeedLimit());
    }
    
    SECTION("no alert when a speed is less then a speed limit")
    {
        bus.speedLimitCallback(SpeedLimitDetected{35});
        bus.speedUpdateCallback(SpeedUpdate{34L});
        REQUIRE(bus.commandsPublished == 0);
    }
    
    SECTION("alert when a speed limit is less then a speed ")
    {
        bus.speedLimitCallback(SpeedLimitDetected{35});
        bus.speedUpdateCallback(SpeedUpdate{40L});
        REQUIRE(bus.commandsPublished == 1);
    }
    
    SECTION("last UT")
    {
        bus.speedLimitCallback(SpeedLimitDetected{35});
        bus.speedUpdateCallback(SpeedUpdate{30L});
        bus.speedLimitCallback(SpeedLimitDetected{25});
        REQUIRE(bus.commandsPublished == 1);
    }
}


