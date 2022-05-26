#include "veins_inet/veins_inet.h"
#include<fstream>
#include<iostream>
#include "veins_inet/vfognetsim/mecoMessages/VeinsInetAppBaseForMeco.h"

class VEINS_INET_API VeinsInetAppForMeco : public veins::VeinsInetAppBaseForMeco {
protected:
    bool haveForwarded = false;
    std::ofstream myfile;
    int fileNum = 0;
    std::fstream fout, foutb, foutc;
    int e1 = 0;
    double qos = 0;

protected:
    virtual bool startApplication() override;
    virtual bool stopApplication() override;
    virtual void processPacket(std::shared_ptr<inet::Packet> pk) override;

public:
    VeinsInetAppForMeco();
    ~VeinsInetAppForMeco();
};
