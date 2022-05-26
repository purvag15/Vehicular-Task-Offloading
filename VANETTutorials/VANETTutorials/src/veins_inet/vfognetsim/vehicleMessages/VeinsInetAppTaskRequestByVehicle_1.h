#include "veins_inet/veins_inet.h"

#include "veins_inet/vfognetsim/vehicleMessages/VeinsInetAppBaseTaskRequestByVehicle_1.h"

class VEINS_INET_API VeinsInetAppTaskRequestByVehicle_1 : public veins::VeinsInetAppBaseTaskRequestByVehicle_1 {
protected:
    bool haveForwarded = false;

protected:
    virtual bool startApplication() override;
    virtual bool stopApplication() override;
    virtual void processPacket(std::shared_ptr<inet::Packet> pk) override;

public:
    VeinsInetAppTaskRequestByVehicle_1();
    ~VeinsInetAppTaskRequestByVehicle_1();
};
