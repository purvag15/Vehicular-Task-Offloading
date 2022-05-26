#include "veins_inet/veins_inet.h"

#include "veins_inet/vfognetsim/edgeMessages/VeinsInetAppBaseForEdge1.h"

class VEINS_INET_API VeinsInetAppForEdge1 : public veins::VeinsInetAppBaseForEdge1 {
protected:
    bool haveForwarded = false;

protected:
    virtual bool startApplication() override;
    virtual bool stopApplication() override;
    virtual void processPacket(std::shared_ptr<inet::Packet> pk) override;

public:
    VeinsInetAppForEdge1();
    ~VeinsInetAppForEdge1();
};
