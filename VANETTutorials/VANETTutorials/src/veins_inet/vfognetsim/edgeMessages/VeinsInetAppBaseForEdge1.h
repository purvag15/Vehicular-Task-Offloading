#include <vector>

#include "veins_inet/veins_inet.h"

#include "inet/common/INETDefs.h"

#include "inet/applications/base/ApplicationBase.h"
#include "inet/transportlayer/contract/udp/UdpSocket.h"
#include "veins_inet/VeinsInetMobility.h"
#include "veins/modules/utility/TimerManager.h"

namespace veins {

class VEINS_INET_API VeinsInetAppBaseForEdge1 : public inet::ApplicationBase, public inet::UdpSocket::ICallback {
protected:
    veins::VeinsInetMobility* mobility;
    veins::TraCICommandInterface* traci;
    veins::TraCICommandInterface::Vehicle* traciVehicle;
    veins::TimerManager timerManager{this};

    int id;
    inet::L3Address  srcAddresses;
    inet::L3Address  destAddresses;
    //std::vector<inet::L3Address>  destAddress;
    const int portNumber = 5000;
    inet::L3Address localAddress;
    int localPort = -1, destPort = -1;
    inet::UdpSocket socket;
    std::vector<std::string> destAddressStr;

protected:
    virtual int numInitStages() const override;
    virtual void initialize(int stage) override;
    virtual void handleStartOperation(inet::LifecycleOperation* doneCallback) override;
    virtual bool startApplication();
    virtual bool stopApplication();
    virtual void handleStopOperation(inet::LifecycleOperation* doneCallback) override;
    virtual void handleCrashOperation(inet::LifecycleOperation* doneCallback) override;
    virtual void finish() override;

    virtual void refreshDisplay() const override;
    virtual void handleMessageWhenUp(inet::cMessage* msg) override;

    virtual void socketDataArrived(inet::UdpSocket* socket, inet::Packet* packet) override;
    virtual void socketErrorArrived(inet::UdpSocket* socket, inet::Indication* indication) override;
    virtual void socketClosed(inet::UdpSocket* socket) override;

    virtual std::unique_ptr<inet::Packet> createPacket(std::string name);
    virtual void processPacket(std::shared_ptr<inet::Packet> pk);
    virtual void timestampPayload(inet::Ptr<inet::Chunk> payload);
    virtual void sendPacketToRSU(std::unique_ptr<inet::Packet> pk, int id);
    virtual void sendPacketToMECO(std::unique_ptr<inet::Packet> pk);

public:
    VeinsInetAppBaseForEdge1();
    ~VeinsInetAppBaseForEdge1();
};

} // namespace veins



