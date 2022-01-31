#ifndef AUTO_BRAKE
#define AUTO_BRAKE

#include "Events.h"
#include "MockServiceBus.h"

class AutoBrake
{
public:
    AutoBrake(IServiceBus& bus):
              speed_mps{0},
              collision_threshold_s{5},
              speedLimit{39}
    {
        bus.subscribe([this, &bus](const SpeedUpdate& update){
            speed_mps = update.velocity_mps;
            if(update.velocity_mps > speedLimit)
            {
                bus.publish(BrakeCommand{0});
            }
        });
        
        bus.subscribe([this, &bus](const CarDetected& cd){
            const auto relativeVelocityMps = speed_mps - cd.velocity_mps;
            const auto timeToCollision = cd.distance_m / relativeVelocityMps;
            if(timeToCollision > 0 &&
                timeToCollision <= collision_threshold_s)
            {
                bus.publish(BrakeCommand{timeToCollision});
            }
        });
        bus.subscribe([this, &bus](const SpeedLimitDetected& update){
            speedLimit = update.speed_mps;
            if(speed_mps > update.speed_mps)
            {
                bus.publish(BrakeCommand{0});
            }
        });
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
    
    unsigned short getSpeedLimit()
    {
        return speedLimit;
    }

private:
    double collision_threshold_s;
    double speed_mps;
    unsigned short speedLimit;
};
#endif//SERVICE_BUS
