#ifndef SERVICE_BUS
#define SERVICE_BUS

#include "Events.h"

class ServiceBus
{
public:
    void publish(const BrakeCommand&);
};
#endif//SERVICE_BUS
