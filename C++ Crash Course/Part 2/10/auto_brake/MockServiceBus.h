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
    
    BrakeCommand lastCommand{};
    int commandsPublished{};
    SpeedUpdateCallback speedUpdateCallback{};
    CarDetectedCallback carDetectedCallback{};
};
