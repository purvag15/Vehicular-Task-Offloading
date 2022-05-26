#include "veins_inet/vfognetsim/rsuMessages/VeinsInetAppBaseForRSU1.h"

#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/packet/Packet.h"
#include "inet/common/TagBase_m.h"
#include "inet/common/TimeTag_m.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/networklayer/common/L3AddressTag_m.h"
#include "inet/transportlayer/contract/udp/UdpControlInfo_m.h"
#include "inet/applications/vfognetsim/VehicleMessages/TaskRequestByVehicle_m.h"

namespace veins {

using namespace inet;

Define_Module(VeinsInetAppBaseForRSU1);

VeinsInetAppBaseForRSU1::VeinsInetAppBaseForRSU1()
{
}

int VeinsInetAppBaseForRSU1::numInitStages() const
{
    return inet::NUM_INIT_STAGES;
}

void VeinsInetAppBaseForRSU1::initialize(int stage)
{
    ApplicationBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
    }
}

void VeinsInetAppBaseForRSU1::handleStartOperation(LifecycleOperation* operation)
{
    socket.setOutputGate(gate("socketOut"));
    socket.bind(L3Address(), portNumber);
    socket.setCallback(this);
    bool ok = startApplication();
    ASSERT(ok);
}

bool VeinsInetAppBaseForRSU1::startApplication()
{

    return true;
}

bool VeinsInetAppBaseForRSU1::stopApplication()
{
    return true;
}

void VeinsInetAppBaseForRSU1::handleStopOperation(LifecycleOperation* operation)
{
    bool ok = stopApplication();
    ASSERT(ok);

    socket.close();
}

void VeinsInetAppBaseForRSU1::handleCrashOperation(LifecycleOperation* operation)
{
    socket.destroy();
}

void VeinsInetAppBaseForRSU1::finish()
{
    ApplicationBase::finish();
}

VeinsInetAppBaseForRSU1::~VeinsInetAppBaseForRSU1()
{
}

void VeinsInetAppBaseForRSU1::refreshDisplay() const
{
    ApplicationBase::refreshDisplay();

    char buf[100];
    sprintf(buf, "okay");
    getDisplayString().setTagArg("t", 0, buf);
}

void VeinsInetAppBaseForRSU1::handleMessageWhenUp(cMessage* msg)
{
    if (timerManager.handleMessage(msg)) return;

    if (msg->isSelfMessage()) {
        throw cRuntimeError("This module does not use custom self messages");
        return;
    }

    socket.processMessage(msg);
}

void VeinsInetAppBaseForRSU1::socketDataArrived(UdpSocket* socket, Packet* packet)
{
    auto pk = std::shared_ptr<inet::Packet>(packet);

    // ignore local echoes
    auto srcAddr = pk->getTag<L3AddressInd>()->getSrcAddress();
    if (srcAddr == Ipv4Address::LOOPBACK_ADDRESS) {
        EV_DEBUG << "Ignored local echo: " << pk.get() << endl;
        return;
    }

    // statistics
    emit(packetReceivedSignal, pk.get());

    // process incoming packet
    processPacket(pk);
}

void VeinsInetAppBaseForRSU1::socketErrorArrived(UdpSocket* socket, Indication* indication)
{
    EV_WARN << "Ignoring UDP error report " << indication->getName() << endl;
    delete indication;
}

void VeinsInetAppBaseForRSU1::socketClosed(UdpSocket* socket)
{
    if (operationalState == State::STOPPING_OPERATION) {
        startActiveOperationExtraTimeOrFinish(-1);
    }
}

void VeinsInetAppBaseForRSU1::timestampPayload(inet::Ptr<inet::Chunk> payload)
{
    payload->removeTagIfPresent<CreationTimeTag>(b(0), b(-1));
    auto creationTimeTag = payload->addTag<CreationTimeTag>();
    creationTimeTag->setCreationTime(simTime());
}

void VeinsInetAppBaseForRSU1::sendPacketToMeco(std::unique_ptr<inet::Packet> pk)
{
    emit(packetSentSignal, pk.get());
    L3AddressResolver().tryResolve("10.0.0.4", destAddresses);
    socket.sendTo(pk.release(), destAddresses, 5000);
}

void VeinsInetAppBaseForRSU1::sendPacketToEdge(std::unique_ptr<inet::Packet> pk, int id)
{
    emit(packetSentSignal, pk.get());
    emit(packetSentSignal, pk.get());
    if(id == 1)
    {
        L3AddressResolver().tryResolve("10.0.0.1", destAddresses);
    }
    else if(id == 2)
    {
        L3AddressResolver().tryResolve("10.0.0.6", destAddresses);
    }
    socket.sendTo(pk.release(), destAddresses, 5000);
}

void VeinsInetAppBaseForRSU1::sendPacketToNode(std::unique_ptr<inet::Packet> pk)
{
    emit(packetSentSignal, pk.get());
    socket.sendTo(pk.release(), srcAddresses, 5000);
}

std::unique_ptr<inet::Packet> VeinsInetAppBaseForRSU1::createPacket(std::string name)
{
    return std::unique_ptr<Packet>(new Packet(name.c_str()));
}

void VeinsInetAppBaseForRSU1::processPacket(std::shared_ptr<inet::Packet> pk)
{

}

} // namespace veins



