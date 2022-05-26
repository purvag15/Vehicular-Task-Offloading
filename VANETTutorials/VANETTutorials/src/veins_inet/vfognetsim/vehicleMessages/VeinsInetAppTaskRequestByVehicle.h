#include "veins_inet/veins_inet.h"

#include "veins_inet/vfognetsim/vehicleMessages/VeinsInetAppBaseTaskRequestByVehicle.h"

class VEINS_INET_API VeinsInetAppTaskRequestByVehicle : public veins::VeinsInetAppBaseTaskRequestByVehicle {
protected:
    bool haveForwarded = false;

protected:
    virtual bool startApplication() override;
    virtual bool stopApplication() override;
    virtual void processPacket(std::shared_ptr<inet::Packet> pk) override;

public:
    VeinsInetAppTaskRequestByVehicle();
    ~VeinsInetAppTaskRequestByVehicle();
};
