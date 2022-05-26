#include "veins_inet/vfognetsim/rsuMessages/VeinsInetAppForRSU.h"

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

Define_Module(VeinsInetAppForRSU);

VeinsInetAppForRSU::VeinsInetAppForRSU()
{
}

bool VeinsInetAppForRSU::startApplication()
{
    // host[0] should stop at t=20s
        //if (getParentModule()->getIndex() == 0) {
        auto callback = [this]() {
            //getParentModule()->getDisplayString().setTagArg("i", 1, "red");

            //traciVehicle->setSpeed(0);

            /*auto payload = makeShared<TaskRequestByVehicle>();
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
            sendPacket(std::move(packet));*/

        };
        timerManager.create(veins::TimerSpecification(callback).oneshotAt(SimTime(20, SIMTIME_S)));
    //}

    return true;
}

bool VeinsInetAppForRSU::stopApplication()
{
    return true;
}

VeinsInetAppForRSU::~VeinsInetAppForRSU()
{
}

void VeinsInetAppForRSU::processPacket(std::shared_ptr<inet::Packet> pk)
{
//    if(strcmp(pk->getName(),"MIPSAdvertisementByEdge")==0)
//    {
//        auto payload = makeShared<MIPSAckByRSU>();
//                    timestampPayload(payload);
//                    payload->setChunkLength(B(100));
//                    payload->setRsuID(1);
//                    payload->setRm_MIPS((pk->peekData<MIPSAdvertisementByEdge>())->getRm_MIPS());
//                    payload->setEdgeID((pk->peekData<MIPSAdvertisementByEdge>())->getEdgeID());
//                    EV_INFO << "**************************************" <<  endl;
//                    EV_INFO << "**************************************" <<  endl;
//                    EV_INFO << "RSU Send packet: MIPSAckByRSU" << payload << endl;
//                    EV_INFO << "**************************************" <<  endl;
//                    EV_INFO << "**************************************" <<  endl;
//                    auto packet = createPacket("MIPSAckByRSU");
//
//                    packet->insertAtBack(payload);
//                    sendPacket(std::move(packet));
//    }
    if(strcmp(pk->getName(),"TaskRequestByVehicle")==0)
        {
            auto payload = makeShared<TaskRequestAckByRSU>();
                        timestampPayload(payload);
                        payload->setChunkLength(B(100));
                        payload->setRsuID(1);
                        payload->setTaskID((pk->peekData<TaskRequestByVehicle>())->getTaskID());
                        payload->setVehicleID((pk->peekData<TaskRequestByVehicle>())->getVehicleID());
                        EV_INFO << "**************************************" <<  endl;
                        EV_INFO << "**************************************" <<  endl;
                        EV_INFO << "RSU Send packet: TaskRequestAckByRSU" << payload << endl;
                        EV_INFO << "**************************************" <<  endl;
                        EV_INFO << "**************************************" <<  endl;
                        auto packet = createPacket("TaskRequestAckByRSU");

                        packet->insertAtBack(payload);
                        sendPacket(std::move(packet));
        }
    if(strcmp(pk->getName(),"TaskRequestByVehicle")==0)
            {
                auto payload = makeShared<TaskAssignmentByRSU>();
                            timestampPayload(payload);
                            payload->setChunkLength(B(100));
                            payload->setRsuID(1);
                            payload->setTaskID((pk->peekData<TaskRequestByVehicle>())->getTaskID());
                            payload->setVehicleID((pk->peekData<TaskRequestByVehicle>())->getVehicleID());
//                            payload->setRSUId((pk->peekData<TaskRequestByVehicle>())->getRSUId());
                            EV_INFO << "**************************************" <<  endl;
                            EV_INFO << "**************************************" <<  endl;
                            EV_INFO << "RSU Send packet: TaskAssignmentByRSU" << payload << endl;
                            EV_INFO << "**************************************" <<  endl;
                            EV_INFO << "**************************************" <<  endl;
                            auto packet = createPacket("TaskAssignmentByRSU");

                            packet->insertAtBack(payload);
                            sendPacket(std::move(packet));
            }
    if(strcmp(pk->getName(),"TaskCompletionMsgByEdge")==0)
                {
                    auto payload = makeShared<TaskCompletionAckByRSU>();
                                timestampPayload(payload);
                                payload->setChunkLength(B(100));
                                payload->setRsuID(1);
                                payload->setEdgeID((pk->peekData<TaskCompletionMsgByEdge>())->getEdgeID());
                                payload->setTaskID((pk->peekData<TaskCompletionMsgByEdge>())->getTaskID());
                                payload->setVehicleID((pk->peekData<TaskCompletionMsgByEdge>())->getVehicleID());
                                EV_INFO << "**************************************" <<  endl;
                                EV_INFO << "**************************************" <<  endl;
                                EV_INFO << "RSU Send packet: TaskCompletionAckByRSU" << payload << endl;
                                EV_INFO << "**************************************" <<  endl;
                                EV_INFO << "**************************************" <<  endl;
                                auto packet = createPacket("TaskCompletionAckByRSU");

                                packet->insertAtBack(payload);
                                sendPacket(std::move(packet));
                }
    if(strcmp(pk->getName(),"TaskCompletionMsgByEdge")==0)
                    {
                        auto payload = makeShared<TaskCompletionMsgByRSU>();
                                    timestampPayload(payload);
                                    payload->setChunkLength(B(100));
                                    payload->setRsuID(1);
                                    payload->setTaskID((pk->peekData<TaskCompletionMsgByEdge>())->getTaskID());
                                    payload->setVehicleID((pk->peekData<TaskCompletionMsgByEdge>())->getVehicleID());
                                    EV_INFO << "**************************************" <<  endl;
                                    EV_INFO << "**************************************" <<  endl;
                                    EV_INFO << "RSU Send packet: TaskCompletionMsgByRSU" << payload << endl;
                                    EV_INFO << "**************************************" <<  endl;
                                    EV_INFO << "**************************************" <<  endl;
                                    auto packet = createPacket("TaskCompletionMsgByRSU");

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


