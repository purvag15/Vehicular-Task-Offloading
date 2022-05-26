#include "veins_inet/veins_inet.h"

#include "veins_inet/vfognetsim/rsuMessages/VeinsInetAppBaseForRSU.h"

class VEINS_INET_API VeinsInetAppForRSU : public veins::VeinsInetAppBaseForRSU {
protected:
    bool haveForwarded = false;

protected:
    virtual bool startApplication() override;
    virtual bool stopApplication() override;
    virtual void processPacket(std::shared_ptr<inet::Packet> pk) override;

public:
    VeinsInetAppForRSU();
    ~VeinsInetAppForRSU();
};

