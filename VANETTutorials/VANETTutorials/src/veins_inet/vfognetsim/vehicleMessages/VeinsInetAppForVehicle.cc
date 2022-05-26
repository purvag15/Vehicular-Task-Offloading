#include "veins_inet/vfognetsim/vehicleMessages/VeinsInetAppForVehicle.h"

#include "veins_inet/vfognetsim/edgeMessages/MIPSAdvertisementByEdge_m.h"
#include "veins_inet/vfognetsim/edgeMessages/TaskAssignmentAckByEdge_m.h"
#include "veins_inet/vfognetsim/edgeMessages/TaskCompletionMsgByEdge_m.h"

#include "veins_inet/vfognetsim/rsuMessages/MIPSAckByRSU_m.h"
#include "veins_inet/vfognetsim/rsuMessages/TaskAssignmentByRSU_m.h"
#include "veins_inet/vfognetsim/rsuMessages/TaskCompletionAckByRSU_m.h"
#include "veins_inet/vfognetsim/rsuMessages/TaskCompletionMsgByRSU_m.h"
#include "veins_inet/vfognetsim/rsuMessages/TaskRequestAckByRSU_m.h"

#include "veins_inet/vfognetsim/vehicleMessages/TaskCompletionAckByVehicle_m.h"
#include "veins_inet/vfognetsim/vehicleMessages/TaskRequestByVehicle_m.h"

#include "inet/common/ModuleAccess.h"
#include "inet/common/packet/Packet.h"
#include "inet/common/TagBase_m.h"
#include "inet/common/TimeTag_m.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/networklayer/common/L3AddressTag_m.h"
#include "inet/transportlayer/contract/udp/UdpControlInfo_m.h"
#include<string>
//#include "veins_inet/vfognetsim/vehicleMessages/TaskCompletionAckByVehicle_m.h"
//#include "veins_inet/vfognetsim/vehicleMessages/TaskRequestByVehicle_m.h"

using namespace inet;

Define_Module(VeinsInetAppForVehicle);

VeinsInetAppForVehicle::VeinsInetAppForVehicle()
{
}

bool VeinsInetAppForVehicle::startApplication()
{
    // host[0] should stop at t=20s
        if (getParentModule()->getIndex() == 0) {
        auto callback = [this]() {
            getParentModule()->getDisplayString().setTagArg("i", 1, "red");

            traciVehicle->setSpeed(0);

            auto payload = makeShared<TaskRequestByVehicle>();
            timestampPayload(payload);
            payload->setChunkLength(B(100));
            payload->setTaskID(1);
            payload->setRq_MIPS(100);
            payload->setVehicleID(1);
            EV_INFO << "**************************************" <<  endl;
            EV_INFO << "**************************************" <<  endl;
            EV_INFO << "Send packet: " << payload << endl;
            EV_INFO << "**************************************" <<  endl;
            EV_INFO << "**************************************" <<  endl;
            auto packet = createPacket("TaskRequestByVehicle");

            packet->insertAtBack(payload);
            sendPacket(std::move(packet));

        };
        timerManager.create(veins::TimerSpecification(callback).oneshotAt(SimTime(20, SIMTIME_S)));
    }

    return true;
}

bool VeinsInetAppForVehicle::stopApplication()
{
    return true;
}

VeinsInetAppForVehicle::~VeinsInetAppForVehicle()
{
}

void VeinsInetAppForVehicle::processPacket(std::shared_ptr<inet::Packet> pk)
{
    if(strcmp(pk->getName(),"TaskRequestByVehicle")==0)
    {
        auto payload = makeShared<TaskRequestByVehicle>();
                    timestampPayload(payload);
                    payload->setChunkLength(B(100));
                    payload->setTaskID(1);
                    payload->setRq_MIPS(100);
                    payload->setVehicleID(1);
                    EV_INFO << "**************************************" <<  endl;
                    EV_INFO << "**************************************" <<  endl;
                    EV_INFO << "After receiving Send packet: TaskRequestByVehicle" << payload << endl;
                    EV_INFO << "**************************************" <<  endl;
                    EV_INFO << "**************************************" <<  endl;
                    auto packet = createPacket("TaskRequestByVehicle");

                    packet->insertAtBack(payload);
                    sendPacket(std::move(packet));
    }
    if(strcmp(pk->getName(),"TaskCompletionMsgByRSU")==0)
                    {
                        auto payload = makeShared<TaskCompletionAckByVehicle>();
                                    timestampPayload(payload);
                                    payload->setChunkLength(B(100));
                                    payload->setRsuID((pk->peekData<TaskCompletionMsgByRSU>())->getRsuID());
                                    payload->setTaskID((pk->peekData<TaskCompletionMsgByRSU>())->getTaskID());
                                    payload->setVehicleID(1);
                                    EV_INFO << "**************************************" <<  endl;
                                    EV_INFO << "**************************************" <<  endl;
                                    EV_INFO << "RSU Send packet: TaskCompletionAckByVehicle" << payload << endl;
                                    EV_INFO << "**************************************" <<  endl;
                                    EV_INFO << "**************************************" <<  endl;
                                    auto packet = createPacket("TaskCompletionAckByVehicle");

                                    packet->insertAtBack(payload);
                                    sendPacket(std::move(packet));
                    }
   // getParentModule()->getDisplayString().setTagArg("i", 1, "green");

    //traciVehicle->changeRoute(payload->getRoadId(), 999.9);

    //if (haveForwarded) return;

    //auto packet = createPacket("relay");
   // packet->insertAtBack(payload);
   // sendPacket(std::move(packet));

    //haveForwarded = true;
}

