#ifndef AUTO_BRAKE
#define AUTO_BRAKE

#include "Events.h"
#include "MockServiceBus.h"

class AutoBrake
{
public:
    AutoBrake(IServiceBus& bus):
              speed_mps{0},
              collision_threshold_s{5}
    {
    }
    
    void set_collision_threshold_s(double x)
    {
        if(x < 1L) throw std::invalid_argument{"Collision less than 1"};
        collision_threshold_s = x;
    }
    
    double get_collision_threshold_s() const
    {
        return collision_threshold_s;
    }
    
    double get_speed_mps() const
    {
        return speed_mps;
    }

private:
    double collision_threshold_s;
    double speed_mps;
};
#endif//SERVICE_BUS
