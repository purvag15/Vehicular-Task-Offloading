#include "veins_inet/vfognetsim/mecoMessages/VeinsInetAppBaseForMeco.h"

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

Define_Module(VeinsInetAppBaseForMeco);

VeinsInetAppBaseForMeco::VeinsInetAppBaseForMeco()
{
}

int VeinsInetAppBaseForMeco::numInitStages() const
{
    return inet::NUM_INIT_STAGES;
}

void VeinsInetAppBaseForMeco::initialize(int stage)
{
    ApplicationBase::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {
        localPort = par("localPort");
        destPort = par("destPort");
    }
}

void VeinsInetAppBaseForMeco::handleStartOperation(LifecycleOperation* operation)
{
    //mobility = veins::VeinsInetMobilityAccess().get(getParentModule());
    //traci = mobility->getCommandInterface();
    //traciVehicle = mobility->getVehicleCommandInterface();

/*    L3AddressResolver().tryResolve("224.0.0.1", destAddresses);
    ASSERT(!destAddress.isUnspecified());*/

    socket.setOutputGate(gate("socketOut"));
    socket.bind(L3Address(), portNumber);
    //const char *localAddress = par("localAddress");
    //socket.bind(*localAddress ? L3AddressResolver().resolve(localAddress) : L3Address(), 5000);

/*    const char* interface = par("interface");
    ASSERT(interface[0]);
    IInterfaceTable* ift = getModuleFromPar<IInterfaceTable>(par("interfaceTableModule"), this);
    InterfaceEntry* ie = ift->findInterfaceByName(interface);
    ASSERT(ie);
    socket.setMulticastOutputInterface(ie->getInterfaceId());

    MulticastGroupList mgl = ift->collectMulticastGroups();
    socket.joinLocalMulticastGroups(mgl);*/

    socket.setCallback(this);

/*    socket.setOutputGate(gate("socketOut"));
    socket.bind(Ipv4Address("10.0.0.1"), 5000);
    socket.connect(Ipv4Address("10.0.0.1"), 5000);
    socket.setCallback(this);*/
    bool ok = startApplication();
    ASSERT(ok);
}

bool VeinsInetAppBaseForMeco::startApplication()
{
    return true;
}

bool VeinsInetAppBaseForMeco::stopApplication()
{
    return true;
}

void VeinsInetAppBaseForMeco::handleStopOperation(LifecycleOperation* operation)
{
    bool ok = stopApplication();
    ASSERT(ok);

    socket.close();
}

void VeinsInetAppBaseForMeco::handleCrashOperation(LifecycleOperation* operation)
{
    socket.destroy();
}

void VeinsInetAppBaseForMeco::finish()
{
    ApplicationBase::finish();
}

VeinsInetAppBaseForMeco::~VeinsInetAppBaseForMeco()
{
}

void VeinsInetAppBaseForMeco::refreshDisplay() const
{
    ApplicationBase::refreshDisplay();

    char buf[100];
    sprintf(buf, "okay");
    getDisplayString().setTagArg("t", 0, buf);
}

void VeinsInetAppBaseForMeco::handleMessageWhenUp(cMessage* msg)
{
    if (timerManager.handleMessage(msg)) return;

    if (msg->isSelfMessage()) {
        throw cRuntimeError("This module does not use custom self messages");
        return;
    }

    socket.processMessage(msg);
}

void VeinsInetAppBaseForMeco::socketDataArrived(UdpSocket* socket, Packet* packet)
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

void VeinsInetAppBaseForMeco::socketErrorArrived(UdpSocket* socket, Indication* indication)
{
    EV_WARN << "Ignoring UDP error report " << indication->getName() << endl;
    delete indication;
}

void VeinsInetAppBaseForMeco::socketClosed(UdpSocket* socket)
{
    if (operationalState == State::STOPPING_OPERATION) {
        startActiveOperationExtraTimeOrFinish(-1);
    }
}

void VeinsInetAppBaseForMeco::timestampPayload(inet::Ptr<inet::Chunk> payload)
{
    payload->removeTagIfPresent<CreationTimeTag>(b(0), b(-1));
    auto creationTimeTag = payload->addTag<CreationTimeTag>();
    creationTimeTag->setCreationTime(simTime());
}

void VeinsInetAppBaseForMeco::sendPacketToRSU(std::unique_ptr<inet::Packet> pk)
{
    emit(packetSentSignal, pk.get());
    //socket.sendTo(pk.release(), destAddresses, 5000);
//    L3AddressResolver().tryResolve("10.0.0.2", destAddresses);
    socket.sendTo(pk.release(), srcAddresses, 5000);
    //socket.sendTo(pk.release(), Ipv4Address("10.0.0.2"), 5000);
}

void VeinsInetAppBaseForMeco::sendPacketToEdge(std::unique_ptr<inet::Packet> pk, int id)
{
    emit(packetSentSignal, pk.get());
    //socket.sendTo(pk.release(), destAddresses, 5000);
//    int rsu = rand()%2;
//    if(id == 0)
//        socket.sendTo(pk.release(), srcAddresses, 5000);
        if(id == 2)
            L3AddressResolver().tryResolve("10.0.0.6", destAddresses);
        else if(id == 1)
            L3AddressResolver().tryResolve("10.0.0.1", destAddresses);
        else
            L3AddressResolver().tryResolve("10.0.0.7", destAddresses);
//    L3AddressResolver().tryResolve("10.0.0.1", destAddresses);
    socket.sendTo(pk.release(), destAddresses, 5000);
    //socket.sendTo(pk.release(), Ipv4Address("10.0.0.2"), 5000);
}

std::unique_ptr<inet::Packet> VeinsInetAppBaseForMeco::createPacket(std::string name)
{
    return std::unique_ptr<Packet>(new Packet(name.c_str()));
}

void VeinsInetAppBaseForMeco::processPacket(std::shared_ptr<inet::Packet> pk)
{

}

} // namespace veins

