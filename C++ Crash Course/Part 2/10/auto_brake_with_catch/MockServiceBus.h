#include "IServiceBus.h"

struct MockServiceBus : IServiceBus
{
    void publish(const BrakeCommand& cmd) override 
    {
        commandsPublished++;
        lastCommand = cmd;
    }
    
    void subscribe(SpeedUpdateCallback callback)
    {
        speedUpdateCallback = callback;
    }
    
    void subscribe(CarDetectedCallback callback)
    {
        carDetectedCallback = callback;
    }
    
    virtual void subscribe(SpeedLimitDetectedCallback callback)
    {
        speedLimitCallback = callback;
    }
    
    BrakeCommand lastCommand{};
    int commandsPublished{};
    SpeedUpdateCallback speedUpdateCallback{};
    CarDetectedCallback carDetectedCallback{};
    SpeedLimitDetectedCallback speedLimitCallback{};
};
