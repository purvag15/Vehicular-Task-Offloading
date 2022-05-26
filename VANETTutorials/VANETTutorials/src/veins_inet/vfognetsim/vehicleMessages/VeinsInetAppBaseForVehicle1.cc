#include "veins_inet/vfognetsim/vehicleMessages/VeinsInetAppBaseForVehicle1.h"

#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/packet/Packet.h"
#include "inet/common/TagBase_m.h"
#include "inet/common/TimeTag_m.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/networklayer/common/L3AddressTag_m.h"
#include "inet/transportlayer/contract/udp/UdpControlInfo_m.h"
#include "inet/applications/vfognetsim/VehicleMessages/TaskCompletionAckByVehicle_m.h"
#include "inet/applications/vfognetsim/VehicleMessages/TaskRequestByVehicle_m.h"

namespace veins {

using namespace inet;

Define_Module(VeinsInetAppBaseForVehicle1);

VeinsInetAppBaseForVehicle1::VeinsInetAppBaseForVehicle1()
{
}

int VeinsInetAppBaseForVehicle1::numInitStages() const
{
    return inet::NUM_INIT_STAGES;
}

void VeinsInetAppBaseForVehicle1::initialize(int stage)
{
    ApplicationBase::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {
    }
}

void VeinsInetAppBaseForVehicle1::handleStartOperation(LifecycleOperation* operation)
{
    mobility = veins::VeinsInetMobilityAccess().get(getParentModule());
    traci = mobility->getCommandInterface();
    traciVehicle = mobility->getVehicleCommandInterface();
    socket.setOutputGate(gate("socketOut"));
    socket.bind(L3Address(), portNumber);socket.setCallback(this);
    bool ok = startApplication();
    ASSERT(ok);
}

bool VeinsInetAppBaseForVehicle1::startApplication()
{
    return true;
}

bool VeinsInetAppBaseForVehicle1::stopApplication()
{
    return true;
}

void VeinsInetAppBaseForVehicle1::handleStopOperation(LifecycleOperation* operation)
{
    bool ok = stopApplication();
    ASSERT(ok);

    socket.close();
}

void VeinsInetAppBaseForVehicle1::handleCrashOperation(LifecycleOperation* operation)
{
    socket.destroy();
}

void VeinsInetAppBaseForVehicle1::finish()
{
    ApplicationBase::finish();
}

VeinsInetAppBaseForVehicle1::~VeinsInetAppBaseForVehicle1()
{
}

void VeinsInetAppBaseForVehicle1::refreshDisplay() const
{
    ApplicationBase::refreshDisplay();

    char buf[100];
    sprintf(buf, "okay");
    getDisplayString().setTagArg("t", 0, buf);
}

void VeinsInetAppBaseForVehicle1::handleMessageWhenUp(cMessage* msg)
{

    if (timerManager.handleMessage(msg)) return;

    if (msg->isSelfMessage()) {
        throw cRuntimeError("This module does not use custom self messages");
        return;
    }
    socket.processMessage(msg);
}

void VeinsInetAppBaseForVehicle1::socketDataArrived(UdpSocket* socket, Packet* packet)
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

void VeinsInetAppBaseForVehicle1::socketErrorArrived(UdpSocket* socket, Indication* indication)
{
    EV_WARN << "Ignoring UDP error report " << indication->getName() << endl;
    delete indication;
}

void VeinsInetAppBaseForVehicle1::socketClosed(UdpSocket* socket)
{
    if (operationalState == State::STOPPING_OPERATION) {
        startActiveOperationExtraTimeOrFinish(-1);
    }
}

void VeinsInetAppBaseForVehicle1::timestampPayload(inet::Ptr<inet::Chunk> payload)
{
    payload->removeTagIfPresent<CreationTimeTag>(b(0), b(-1));
    auto creationTimeTag = payload->addTag<CreationTimeTag>();
    creationTimeTag->setCreationTime(simTime());
}

void VeinsInetAppBaseForVehicle1::sendPacketToRSU(std::unique_ptr<inet::Packet> pk)
{
    emit(packetSentSignal, pk.get());

    int rsu = rand()%3;
    if(rsu == 0)
        L3AddressResolver().tryResolve("10.0.0.2", destAddresses);
    else if(rsu == 1) L3AddressResolver().tryResolve("10.0.0.5", destAddresses);
    else L3AddressResolver().tryResolve("10.0.0.8", destAddresses);
        socket.sendTo(pk.release(), destAddresses, 5000);
}

std::unique_ptr<inet::Packet> VeinsInetAppBaseForVehicle1::createPacket(std::string name)
{
    return std::unique_ptr<Packet>(new Packet(name.c_str()));
}

void VeinsInetAppBaseForVehicle1::processPacket(std::shared_ptr<inet::Packet> pk)
{
}

} // namespace veins

