#include "veins_inet/veins_inet.h"

#include "veins_inet/vfognetsim/vehicleMessages/VeinsInetAppBaseForVehicle1.h"

class VEINS_INET_API VeinsInetAppForVehicle1 : public veins::VeinsInetAppBaseForVehicle1 {
protected:
    bool haveForwarded = false;

protected:
    virtual bool startApplication() override;
    virtual bool stopApplication() override;
    virtual void processPacket(std::shared_ptr<inet::Packet> pk) override;

public:
    VeinsInetAppForVehicle1();
    ~VeinsInetAppForVehicle1();
};
