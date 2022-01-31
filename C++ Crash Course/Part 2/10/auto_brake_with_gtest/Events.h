#ifndef EVENTS
#define EVENTS

struct SpeedUpdate
{
    double velocity_mps;
};

struct CarDetected 
{
    double distance_m;
    double velocity_mps;
};

struct BrakeCommand
{
    double time_to_collision_s;
};

#endif// EVENTS
