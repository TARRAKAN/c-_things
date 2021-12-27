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
        auto_brake.set_collision_threshold_s(2L);
        bus.speedUpdateCallback(SpeedUpdate{100L});
        bus.carDetectedCallback(CarDetected{1000L, 50L});
        REQUIRE(bus.commandsPublished == 0);
    }
    
    SECTION("alert when imminent")
    {
        auto_brake.set_collision_threshold_s(10L);
        bus.speedUpdateCallback(SpeedUpdate{100L});
        bus.carDetectedCallback(CarDetected{100L, 0L});
        REQUIRE(bus.commandsPublished == 1);
        REQUIRE(bus.lastCommand.time_to_collision_s == Approx(1));
    }
}
