#include "veins_inet/vfognetsim/rsuMessages/VeinsInetAppForRSU1.h"

#include "veins_inet/vfognetsim/edgeMessages/MIPSAdvertisementByEdge_m.h"
#include "veins_inet/vfognetsim/edgeMessages/TaskAssignmentAckByEdge_m.h"
#include "veins_inet/vfognetsim/edgeMessages/TaskCompletionMsgByEdge_m.h"
#include "veins_inet/vfognetsim/edgeMessages/TaskAssignedToVehicle_m.h"

#include "veins_inet/vfognetsim/rsuMessages/MIPSAckByRSU_m.h"
#include "veins_inet/vfognetsim/rsuMessages/MIPSAckByRSUMeco_m.h"
#include "veins_inet/vfognetsim/rsuMessages/TaskAssignmentByRSU_m.h"
#include "veins_inet/vfognetsim/rsuMessages/TaskCompletionAckByRSU_m.h"
#include "veins_inet/vfognetsim/rsuMessages/SendPacket_m.h"
#include "veins_inet/vfognetsim/rsuMessages/TaskCompletionMsgByRSU_m.h"
#include "veins_inet/vfognetsim/rsuMessages/TaskRequestAckByRSU_m.h"

#include "veins_inet/vfognetsim/mecoMessages/MIPSAdvertisementByMeco_m.h"
#include "veins_inet/vfognetsim/mecoMessages/CollectRequests_m.h"

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
#include <fstream>
#include<iostream>

using namespace inet;

Define_Module(VeinsInetAppForRSU1);

VeinsInetAppForRSU1::VeinsInetAppForRSU1()
{
}

bool VeinsInetAppForRSU1::startApplication()
{
        auto callback = [this]() {
        };
    return true;
}

bool VeinsInetAppForRSU1::stopApplication()
{
    return true;
}

VeinsInetAppForRSU1::~VeinsInetAppForRSU1()
{
}

void VeinsInetAppForRSU1::processPacket(std::shared_ptr<inet::Packet> pk)
{
    auto l3Addresses = pk->getTag<L3AddressInd>();
    srcAddresses =  l3Addresses->getSrcAddress();

    if(strcmp(pk->getName(),"TaskRequestByVehicle")==0)
        {
            auto payload = makeShared<TaskRequestAckByRSU>();
                        timestampPayload(payload);
                        payload->setChunkLength(B(100));
                        payload->setRsuID(getIndex());
                        payload->setTaskID((pk->peekData<TaskRequestByVehicle>())->getTaskID());
                        payload->setVehicleID((pk->peekData<TaskRequestByVehicle>())->getVehicleID());
                        EV_INFO << "**************************************" <<  endl;
                        EV_INFO << "**************************************" <<  endl;
                        EV_INFO << "RSU Send packet: TaskRequestAckByRSU" << payload << endl;
                        EV_INFO << "**************************************" <<  endl;
                        EV_INFO << "**************************************" <<  endl;
                        auto packet = createPacket("TaskRequestAckByRSU");

                        packet->insertAtBack(payload);
                        sendPacketToNode(std::move(packet));
        }
    if(strcmp(pk->getName(),"TaskRequestByVehicle")==0 && simTime()<20.3)
            {

                auto payload = makeShared<TaskRequestAckByRSU>();
                            timestampPayload(payload);
                            payload->setChunkLength(B(100));
                            payload->setRsuID(getIndex());
                            payload->setTaskID((pk->peekData<TaskRequestByVehicle>())->getTaskID());
                            payload->setVehicleID((pk->peekData<TaskRequestByVehicle>())->getVehicleID());
                            EV_INFO << "**************************************" <<  endl;
                            EV_INFO << "**************************************" <<  endl;
                            EV_INFO << "RSU Send packet: SendPacket" << payload << endl;
                            EV_INFO << "**************************************" <<  endl;
                            EV_INFO << "**************************************" <<  endl;
                            auto packet = createPacket("SendPacket");

                            packet->insertAtBack(payload);
                            sendPacketToNode(std::move(packet));
            }
    if(strcmp(pk->getName(),"TaskRequestByVehicle")==0)
            {
                auto payload = makeShared<TaskAssignmentByRSU>();
                            timestampPayload(payload);
                            payload->setChunkLength(B(100));
                            payload->setTaskID((pk->peekData<TaskRequestByVehicle>())->getTaskID());
                            payload->setFilename("foot.txt");
                            EV_INFO << "**************************************" <<  endl;
                            EV_INFO << "**************************************" <<  endl;
                            EV_INFO << "RSU Send packet: TaskAssignmentByRSU" << payload << endl;
                            EV_INFO << "**************************************" <<  endl;
                            EV_INFO << "**************************************" <<  endl;
                            auto packet = createPacket("TaskAssignmentByRSU");

                            simtime_t eed = simTime() - pk->getCreationTime();

                            if(simTime()>=stop)
                            {
                                stop += 0.01;
                                start += 0.01;
                                packet->insertAtBack(payload);
                                sendPacketToMeco(std::move(packet));
                            }
                            myfile.open("foot.txt", std::ios::app);

                            if(pk->getCreationTime() > start && pk->getCreationTime() < stop)
                            {
                                myfile << (pk->peekData<TaskRequestByVehicle>())->getRq_MIPS() << " ";
                                myfile << (pk->peekData<TaskRequestByVehicle>())->getTaskSize() << " ";
                                myfile << (pk->peekData<TaskRequestByVehicle>())->getDelayTol() << " ";
                                myfile << (pk->peekData<TaskRequestByVehicle>())->getX() << " ";
                                myfile << (pk->peekData<TaskRequestByVehicle>())->getY() << " ";
                                myfile << (pk->peekData<TaskRequestByVehicle>())->getVehicleID() << " ";
                                myfile << getIndex() << " ";
                                myfile << "\n";
                            }

                            myfile.close();
            }
    if(strcmp(pk->getName(),"VehicleTaskAckByMeco")==0)
    {
        myfile.open("foot.txt", std::ofstream::out | std::ofstream::trunc);
        myfile<<"";
        myfile.close();
    }
    if(strcmp(pk->getName(),"TaskCompletionMsgByEdge")==0)
                {
                    auto payload = makeShared<TaskCompletionAckByRSU>();
                                timestampPayload(payload);
                                payload->setChunkLength(B(100));
                                payload->setRsuID(getIndex());
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
                                sendPacketToEdge(std::move(packet), getIndex());
                }
    if(strcmp(pk->getName(),"TaskCompletionMsgByEdge")==0)
                    {
                        auto payload = makeShared<TaskCompletionMsgByRSU>();
                                    timestampPayload(payload);
                                    payload->setChunkLength(B(100));
                                    payload->setRsuID((pk->peekData<TaskCompletionMsgByEdge>())->getRsuID());
                                    payload->setTaskID((pk->peekData<TaskCompletionMsgByEdge>())->getTaskID());
                                    payload->setVehicleID((pk->peekData<TaskCompletionMsgByEdge>())->getVehicleID());
                                    payload->setResult((pk->peekData<TaskCompletionMsgByEdge>())->getResult());
                                    EV_INFO << "**************************************" <<  endl;
                                    EV_INFO << "**************************************" <<  endl;
                                    EV_INFO << "RSU Send packet: TaskCompletionMsgByRSU" << payload << endl;
                                    EV_INFO << "**************************************" <<  endl;
                                    EV_INFO << "**************************************" <<  endl;
                                    auto packet = createPacket("TaskCompletionMsgByRSU");

                                    packet->insertAtBack(payload);
                                    sendPacketToNode(std::move(packet));
                    }

    if(strcmp(pk->getName(),"CollectRequests")==0)
    {
        std::fstream fout;
        fout.open("prediction.csv", std::ofstream::out | std::ofstream::trunc);
        fout<<"";
        fout.close();

        std::fstream foutb;
        foutb.open("b_prediction.csv", std::ofstream::out | std::ofstream::trunc);
        foutb<<"";
        foutb.close();

        std::fstream foutc;
        foutc.open("c_prediction.csv", std::ofstream::out | std::ofstream::trunc);
        foutc<<"";
        foutc.close();

        auto payload = makeShared<TaskAssignedToVehicle>();
                    timestampPayload(payload);
                    payload->setChunkLength(B(100));
                    payload->setRsuID((pk->peekData<CollectRequests>())->getRsuID());
                    payload->setVehicleID((pk->peekData<CollectRequests>())->getVehicleID());
                    EV_INFO << "**************************************" <<  endl;
                    EV_INFO << "**************************************" <<  endl;
                    EV_INFO << "RSU Send packet: TaskAssignedToVehicle" << payload << endl;
                    EV_INFO << "**************************************" <<  endl;
                    EV_INFO << "**************************************" <<  endl;
                    auto packet = createPacket("TaskAssignedToVehicle");

                    packet->insertAtBack(payload);
                    sendPacketToNode(std::move(packet));
    }
}


