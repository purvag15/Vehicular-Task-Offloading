#include "veins_inet/vfognetsim/vehicleMessages/VeinsInetAppBaseTaskCompletionAckByVehicle.h"

#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/packet/Packet.h"
#include "inet/common/TagBase_m.h"
#include "inet/common/TimeTag_m.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/networklayer/common/L3AddressTag_m.h"
#include "inet/transportlayer/contract/udp/UdpControlInfo_m.h"

namespace veins {

using namespace inet;

Define_Module(VeinsInetAppBaseTaskCompletionAckByVehicle);

VeinsInetAppBaseTaskCompletionAckByVehicle::VeinsInetAppBaseTaskCompletionAckByVehicle()
{
}

int VeinsInetAppBaseTaskCompletionAckByVehicle::numInitStages() const
{
    return inet::NUM_INIT_STAGES;
}

void VeinsInetAppBaseTaskCompletionAckByVehicle::initialize(int stage)
{
    ApplicationBase::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {
    }
}

void VeinsInetAppBaseTaskCompletionAckByVehicle::handleStartOperation(LifecycleOperation* operation)
{
    mobility = veins::VeinsInetMobilityAccess().get(getParentModule());
    traci = mobility->getCommandInterface();
    traciVehicle = mobility->getVehicleCommandInterface();

    L3AddressResolver().tryResolve("224.0.0.1", destAddress);
    ASSERT(!destAddress.isUnspecified());

    socket.setOutputGate(gate("socketOut"));
    socket.bind(L3Address(), portNumber);

    const char* interface = par("interface");
    ASSERT(interface[0]);
    IInterfaceTable* ift = getModuleFromPar<IInterfaceTable>(par("interfaceTableModule"), this);
    InterfaceEntry* ie = ift->findInterfaceByName(interface);
    ASSERT(ie);
    socket.setMulticastOutputInterface(ie->getInterfaceId());

    MulticastGroupList mgl = ift->collectMulticastGroups();
    socket.joinLocalMulticastGroups(mgl);

    socket.setCallback(this);

    bool ok = startApplication();
    ASSERT(ok);
}

bool VeinsInetAppBaseTaskCompletionAckByVehicle::startApplication()
{
    return true;
}

bool VeinsInetAppBaseTaskCompletionAckByVehicle::stopApplication()
{
    return true;
}

void VeinsInetAppBaseTaskCompletionAckByVehicle::handleStopOperation(LifecycleOperation* operation)
{
    bool ok = stopApplication();
    ASSERT(ok);

    socket.close();
}

void VeinsInetAppBaseTaskCompletionAckByVehicle::handleCrashOperation(LifecycleOperation* operation)
{
    socket.destroy();
}

void VeinsInetAppBaseTaskCompletionAckByVehicle::finish()
{
    ApplicationBase::finish();
}

VeinsInetAppBaseTaskCompletionAckByVehicle::~VeinsInetAppBaseTaskCompletionAckByVehicle()
{
}

void VeinsInetAppBaseTaskCompletionAckByVehicle::refreshDisplay() const
{
    ApplicationBase::refreshDisplay();

    char buf[100];
    sprintf(buf, "okay");
    getDisplayString().setTagArg("t", 0, buf);
}

void VeinsInetAppBaseTaskCompletionAckByVehicle::handleMessageWhenUp(cMessage* msg)
{
    if (timerManager.handleMessage(msg)) return;

    if (msg->isSelfMessage()) {
        throw cRuntimeError("This module does not use custom self messages");
        return;
    }

    socket.processMessage(msg);
}

void VeinsInetAppBaseTaskCompletionAckByVehicle::socketDataArrived(UdpSocket* socket, Packet* packet)
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

void VeinsInetAppBaseTaskCompletionAckByVehicle::socketErrorArrived(UdpSocket* socket, Indication* indication)
{
    EV_WARN << "Ignoring UDP error report " << indication->getName() << endl;
    delete indication;
}

void VeinsInetAppBaseTaskCompletionAckByVehicle::socketClosed(UdpSocket* socket)
{
    if (operationalState == State::STOPPING_OPERATION) {
        startActiveOperationExtraTimeOrFinish(-1);
    }
}

void VeinsInetAppBaseTaskCompletionAckByVehicle::timestampPayload(inet::Ptr<inet::Chunk> payload)
{
    payload->removeTagIfPresent<CreationTimeTag>(b(0), b(-1));
    auto creationTimeTag = payload->addTag<CreationTimeTag>();
    creationTimeTag->setCreationTime(simTime());
}

void VeinsInetAppBaseTaskCompletionAckByVehicle::sendPacket(std::unique_ptr<inet::Packet> pk)
{
    emit(packetSentSignal, pk.get());
    socket.sendTo(pk.release(), destAddress, portNumber);
}

std::unique_ptr<inet::Packet> VeinsInetAppBaseTaskCompletionAckByVehicle::createPacket(std::string name)
{
    return std::unique_ptr<Packet>(new Packet(name.c_str()));
}

void VeinsInetAppBaseTaskCompletionAckByVehicle::processPacket(std::shared_ptr<inet::Packet> pk)
{
}

} // namespace veins
