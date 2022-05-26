#include "veins_inet/veins_inet.h"

#include "veins_inet/vfognetsim/vehicleMessages/VeinsInetAppBaseForVehicle.h"

class VEINS_INET_API VeinsInetAppForVehicle : public veins::VeinsInetAppBaseForVehicle {
protected:
    bool haveForwarded = false;

protected:
    virtual bool startApplication() override;
    virtual bool stopApplication() override;
    virtual void processPacket(std::shared_ptr<inet::Packet> pk) override;

public:
    VeinsInetAppForVehicle();
    ~VeinsInetAppForVehicle();
};
