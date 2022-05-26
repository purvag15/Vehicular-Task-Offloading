#include "veins_inet/vfognetsim/edgeMessages/VeinsInetAppForEdge.h"

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

Define_Module(VeinsInetAppForEdge);

VeinsInetAppForEdge::VeinsInetAppForEdge()
{
}

bool VeinsInetAppForEdge::startApplication()
{
    // host[0] should stop at t=20s
        //if (getParentModule()->getIndex() == 0) {
        auto callback = [this]() {
            //getParentModule()->getDisplayString().setTagArg("i", 1, "red");

            //traciVehicle->setSpeed(0);

            auto payload = makeShared<MIPSAdvertisementByEdge>();
            timestampPayload(payload);
            payload->setChunkLength(B(100));
            payload->setRm_MIPS(100);
            payload->setEdgeID(1);
            EV_INFO << "**************************************" <<  endl;
            EV_INFO << "**************************************" <<  endl;
            EV_INFO << "Send packet: " << payload << endl;
            EV_INFO << "**************************************" <<  endl;
            EV_INFO << "**************************************" <<  endl;
            auto packet = createPacket("MIPSAdvertisementByEdge");

            packet->insertAtBack(payload);
            sendPacket(std::move(packet));

        };
        timerManager.create(veins::TimerSpecification(callback).oneshotAt(SimTime(20, SIMTIME_S)));
    //}

    return true;
}

bool VeinsInetAppForEdge::stopApplication()
{
    return true;
}

VeinsInetAppForEdge::~VeinsInetAppForEdge()
{
}

void VeinsInetAppForEdge::processPacket(std::shared_ptr<inet::Packet> pk)
{
    if(strcmp(pk->getName(),"TaskRequestByVehicle")==0)
    {
        auto payload = makeShared<MIPSAdvertisementByEdge>();
                    timestampPayload(payload);
                    payload->setChunkLength(B(100));
                    payload->setRm_MIPS(100);
                    payload->setEdgeID(1);
                    EV_INFO << "**************************************" <<  endl;
                    EV_INFO << "**************************************" <<  endl;
                    EV_INFO << "Edge Send packet: MIPSAdvertisementByEdge" << payload << endl;
                    EV_INFO << "**************************************" <<  endl;
                    EV_INFO << "**************************************" <<  endl;
                    auto packet = createPacket("MIPSAdvertisementByEdge");

                    packet->insertAtBack(payload);
                    sendPacket(std::move(packet));
    }
    if(strcmp(pk->getName(),"TaskAssignmentByRSU")==0)
        {
        auto payload = makeShared<TaskAssignmentAckByEdge>();
                            timestampPayload(payload);
                            payload->setChunkLength(B(100));
                            payload->setTaskID((pk->peekData<TaskAssignmentByRSU>())->getTaskID());
                            payload->setEdgeID(1);
                            payload->setRsuID((pk->peekData<TaskAssignmentByRSU>())->getRsuID());
                            payload->setVehicleID((pk->peekData<TaskAssignmentByRSU>())->getVehicleID());
                            EV_INFO << "**************************************" <<  endl;
                            EV_INFO << "**************************************" <<  endl;
                            EV_INFO << "Edge Send packet: TaskAssignmentAckByEdge" << payload << endl;
                            EV_INFO << "**************************************" <<  endl;
                            EV_INFO << "**************************************" <<  endl;
                            auto packet = createPacket("TaskAssignmentAckByEdge");

                            packet->insertAtBack(payload);
                            sendPacket(std::move(packet));
        }
    if(strcmp(pk->getName(),"TaskAssignmentByRSU")==0)
            {
            auto payload = makeShared<TaskCompletionMsgByEdge>();
                                timestampPayload(payload);
                                payload->setChunkLength(B(100));
                                payload->setTaskID((pk->peekData<TaskAssignmentByRSU>())->getTaskID());
                                payload->setEdgeID(1);
                                payload->setRsuID((pk->peekData<TaskAssignmentByRSU>())->getRsuID());
                                payload->setVehicleID((pk->peekData<TaskAssignmentByRSU>())->getVehicleID());
                                EV_INFO << "**************************************" <<  endl;
                                EV_INFO << "**************************************" <<  endl;
                                EV_INFO << "Edge Send packet: TaskCompletionMsgByEdge" << payload << endl;
                                EV_INFO << "**************************************" <<  endl;
                                EV_INFO << "**************************************" <<  endl;
                                auto packet = createPacket("TaskCompletionMsgByEdge");

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
