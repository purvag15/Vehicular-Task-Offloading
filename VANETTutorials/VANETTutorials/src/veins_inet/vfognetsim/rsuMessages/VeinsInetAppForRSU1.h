#include "veins_inet/veins_inet.h"
#include<string>
#include <fstream>
#include<iostream>
#include "veins_inet/vfognetsim/rsuMessages/VeinsInetAppBaseForRSU1.h"

class VEINS_INET_API VeinsInetAppForRSU1 : public veins::VeinsInetAppBaseForRSU1 {
protected:
    bool haveForwarded = false;
    float start=20;
    float stop=20.01;
    std::ofstream myfile;

protected:
    virtual bool startApplication() override;
    virtual bool stopApplication() override;
    virtual void processPacket(std::shared_ptr<inet::Packet> pk) override;

public:
    VeinsInetAppForRSU1();
    ~VeinsInetAppForRSU1();
};

