#include "veins_inet/vfognetsim/vehicleMessages/VeinsInetAppBaseForVehicle.h"

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

Define_Module(VeinsInetAppBaseForVehicle);

VeinsInetAppBaseForVehicle::VeinsInetAppBaseForVehicle()
{
}

int VeinsInetAppBaseForVehicle::numInitStages() const
{
    return inet::NUM_INIT_STAGES;
}

void VeinsInetAppBaseForVehicle::initialize(int stage)
{
    ApplicationBase::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {
    }
}

void VeinsInetAppBaseForVehicle::handleStartOperation(LifecycleOperation* operation)
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

bool VeinsInetAppBaseForVehicle::startApplication()
{
    return true;
}

bool VeinsInetAppBaseForVehicle::stopApplication()
{
    return true;
}

void VeinsInetAppBaseForVehicle::handleStopOperation(LifecycleOperation* operation)
{
    bool ok = stopApplication();
    ASSERT(ok);

    socket.close();
}

void VeinsInetAppBaseForVehicle::handleCrashOperation(LifecycleOperation* operation)
{
    socket.destroy();
}

void VeinsInetAppBaseForVehicle::finish()
{
    ApplicationBase::finish();
}

VeinsInetAppBaseForVehicle::~VeinsInetAppBaseForVehicle()
{
}

void VeinsInetAppBaseForVehicle::refreshDisplay() const
{
    ApplicationBase::refreshDisplay();

    char buf[100];
    sprintf(buf, "okay");
    getDisplayString().setTagArg("t", 0, buf);
}

void VeinsInetAppBaseForVehicle::handleMessageWhenUp(cMessage* msg)
{

    if (timerManager.handleMessage(msg)) return;

    if (msg->isSelfMessage()) {
        throw cRuntimeError("This module does not use custom self messages");
        return;
    }

    socket.processMessage(msg);

}

void VeinsInetAppBaseForVehicle::socketDataArrived(UdpSocket* socket, Packet* packet)
{
    auto pk = std::shared_ptr<inet::Packet>(packet);
    /*if(strcmp(pk->getName(),"MIPSAdvertisementByEdge")==0)
                    {
        auto payload = makeShared<TaskRequestByVehicle>();
                            timestampPayload(payload);
                            payload->setChunkLength(B(100));
                            payload->setTaskID(1);
                            payload->setRq_MIPS(100);
                            payload->setVehicleID(1);
                            EV_INFO << "**************************************" <<  endl;
                            EV_INFO << "**************************************" <<  endl;
                            EV_INFO << "Send packet: TaskRequestByVehicle" << payload << endl;
                            EV_INFO << "**************************************" <<  endl;
                            EV_INFO << "**************************************" <<  endl;
                            auto packet1 = createPacket("TaskRequestByVehicle");

                            packet1->insertAtBack(payload);
                            sendPacket(std::move(packet1));
                    }
*/                            //sendPacket(std::move(packet));
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

void VeinsInetAppBaseForVehicle::socketErrorArrived(UdpSocket* socket, Indication* indication)
{
    EV_WARN << "Ignoring UDP error report " << indication->getName() << endl;
    delete indication;
}

void VeinsInetAppBaseForVehicle::socketClosed(UdpSocket* socket)
{
    if (operationalState == State::STOPPING_OPERATION) {
        startActiveOperationExtraTimeOrFinish(-1);
    }
}

void VeinsInetAppBaseForVehicle::timestampPayload(inet::Ptr<inet::Chunk> payload)
{
    payload->removeTagIfPresent<CreationTimeTag>(b(0), b(-1));
    auto creationTimeTag = payload->addTag<CreationTimeTag>();
    creationTimeTag->setCreationTime(simTime());
}

void VeinsInetAppBaseForVehicle::sendPacket(std::unique_ptr<inet::Packet> pk)
{
    emit(packetSentSignal, pk.get());
    socket.sendTo(pk.release(), destAddress, portNumber);
}

std::unique_ptr<inet::Packet> VeinsInetAppBaseForVehicle::createPacket(std::string name)
{
    return std::unique_ptr<Packet>(new Packet(name.c_str()));
}

void VeinsInetAppBaseForVehicle::processPacket(std::shared_ptr<inet::Packet> pk)
{
}

} // namespace veins

