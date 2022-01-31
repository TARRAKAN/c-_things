#include <functional>

using SpeedUpdateCallback         = std::function<void(const SpeedUpdate&)>;
using CarDetectedCallback         = std::function<void(const CarDetected&)>;
using SpeedLimitDetectedCallback  = std::function<void(const SpeedLimitDetected&)>;

struct IServiceBus
{
    virtual ~IServiceBus() = default;
    virtual void publish(const BrakeCommand&)           = 0;
    virtual void subscribe(SpeedUpdateCallback)         = 0;
    virtual void subscribe(CarDetectedCallback)         = 0;
    virtual void subscribe(SpeedLimitDetectedCallback)  = 0;
};
