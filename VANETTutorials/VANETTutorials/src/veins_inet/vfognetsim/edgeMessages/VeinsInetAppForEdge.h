#include "veins_inet/veins_inet.h"

#include "veins_inet/vfognetsim/edgeMessages/VeinsInetAppBaseForEdge.h"

class VEINS_INET_API VeinsInetAppForEdge : public veins::VeinsInetAppBaseForEdge {
protected:
    bool haveForwarded = false;

protected:
    virtual bool startApplication() override;
    virtual bool stopApplication() override;
    virtual void processPacket(std::shared_ptr<inet::Packet> pk) override;

public:
    VeinsInetAppForEdge();
    ~VeinsInetAppForEdge();
};
