//#include "service_bus.h"
//#include "auto_brake.h"

#include <cstdio>
#include <stdexcept>
#include "Events.h"
#include "auto_brake.h"

constexpr void assert_that(bool statement, const char message[])
{
    if(!statement) throw std::runtime_error{message};
}
//tests
void initial_speed_is_zero()
{
    MockServiceBus bus{};
    AutoBrake auto_brake{bus};
    assert_that(auto_brake.get_speed_mps() == 0L, "speed not equal 0");
}

void initial_sensitivity_is_five()
{
    MockServiceBus bus{};
    AutoBrake auto_brake{bus};
    assert_that(auto_brake.get_collision_threshold_s() == 5L, "sensitivity isn't 5");
}


void sensitivity_greater_than_1()
{
    MockServiceBus bus{};
    AutoBrake auto_brake{bus};
    try
    {
        auto_brake.set_collision_threshold_s(0.5L);
    }
    catch(const std::exception&)
    {
        return;
    }
    assert_that(false, "no exception thrown");
}

void speed_is_saved()
{
    MockServiceBus bus{};
    AutoBrake auto_brake{bus};
    
    bus.speedUpdateCallback(SpeedUpdate{100L});
    assert_that(100L == auto_brake.get_speed_mps(), "speed isn't saved to 100");
    bus.speedUpdateCallback(SpeedUpdate{50L});
    assert_that(50L == auto_brake.get_speed_mps(), "speed isn't saved to 50");
    bus.speedUpdateCallback(SpeedUpdate{0L});
    assert_that(0L == auto_brake.get_speed_mps(), "speed isn't saved to 0");
}
 
void alert_when_imminent()
{
    MockServiceBus bus{};
    AutoBrake auto_brake{bus};
    auto_brake.set_collision_threshold_s(10L);
    bus.speedUpdateCallback(SpeedUpdate{100L});
    bus.carDetectedCallback(CarDetected{100L, 0L});
    assert_that(bus.commandsPublished == 1, "1bc wn pub");
    assert_that(bus.lastCommand.time_to_collision_s == 1L, "tc n comp corr");
}

void no_alert_when_no_imminent()
{
    MockServiceBus bus{};
    AutoBrake auto_brake{bus};
    auto_brake.set_collision_threshold_s(2L);
    bus.speedUpdateCallback(SpeedUpdate{100L});
    bus.carDetectedCallback(CarDetected{1000L, 50L});
    
    assert_that(bus.commandsPublished == 0, "brake commands published");
}
// 
void run_tests(void(*unit_test)(), const char* name)
{
    try
    {
        unit_test();
        printf("[+] Test %s successful.\n", name);
    }
    catch(const std::exception& e)
    {
        printf("[-] Test failure in %s. %s.\n", name, e.what());
    }
}


int main()
{
    
    //ServiceBus bus{};
    //AutoBrake aut_brake{[&bus](const auto& cmd){bus.publish(cmd);}};
    
    //while(true)
    //{
    //    auto_brake.observe(SpeedUpdate{10L});
    //    auto_brake.observe(CarDetected{250L, 25L});
    //}
    
    run_tests(initial_speed_is_zero, "initial speed is 0");
    run_tests(initial_sensitivity_is_five, "initial sensitivity is 5");
    run_tests(sensitivity_greater_than_1, "sensitivity greater than 1");
    run_tests(speed_is_saved, "speed is saved");
    run_tests(alert_when_imminent, "alert when imminent");
    run_tests(no_alert_when_no_imminent, "no alert when no imminent");
    return 0;
}
