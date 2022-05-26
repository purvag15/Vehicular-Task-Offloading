#include <vector>

#include "veins_inet/veins_inet.h"

#include "inet/common/INETDefs.h"

#include "inet/applications/base/ApplicationBase.h"
#include "inet/transportlayer/contract/udp/UdpSocket.h"
#include "veins_inet/VeinsInetMobility.h"
#include "veins/modules/utility/TimerManager.h"

namespace veins {

class VEINS_INET_API VeinsInetAppBaseForEdge : public inet::ApplicationBase, public inet::UdpSocket::ICallback {
protected:
    veins::VeinsInetMobility* mobility;
    veins::TraCICommandInterface* traci;
    veins::TraCICommandInterface::Vehicle* traciVehicle;
    veins::TimerManager timerManager{this};

    inet::L3Address destAddress;
    const int portNumber = 9001;
    inet::UdpSocket socket;

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
    virtual void sendPacket(std::unique_ptr<inet::Packet> pk);

public:
    VeinsInetAppBaseForEdge();
    ~VeinsInetAppBaseForEdge();
};

} // namespace veins



