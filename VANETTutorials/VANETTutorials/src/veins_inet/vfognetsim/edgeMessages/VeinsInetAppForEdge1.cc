#include "veins_inet/vfognetsim/edgeMessages/VeinsInetAppForEdge1.h"

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

#include "veins_inet/vfognetsim/mecoMessages/CollectRequests_m.h"

#include "inet/common/ModuleAccess.h"
#include "inet/common/packet/Packet.h"
#include "inet/common/TagBase_m.h"
#include "inet/common/TimeTag_m.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/networklayer/common/L3AddressTag_m.h"
#include "inet/transportlayer/contract/udp/UdpControlInfo_m.h"
#include<string>
#include<Windows.h>
#include<fstream>
#include<iostream>

using namespace inet;

Define_Module(VeinsInetAppForEdge1);

VeinsInetAppForEdge1::VeinsInetAppForEdge1()
{
}

bool VeinsInetAppForEdge1::startApplication()
{
    auto callback = [this]() {
    };
    timerManager.create(veins::TimerSpecification(callback).oneshotAt(SimTime(20, SIMTIME_S)));
    return true;
}

bool VeinsInetAppForEdge1::stopApplication()
{
    return true;
}

VeinsInetAppForEdge1::~VeinsInetAppForEdge1()
{
}

void VeinsInetAppForEdge1::processPacket(std::shared_ptr<inet::Packet> pk)
{
    auto l3Addresses = pk->getTag<L3AddressInd>();
    srcAddresses =  l3Addresses->getSrcAddress();

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

        auto payload = makeShared<TaskAssignmentAckByEdge>();
        timestampPayload(payload);
        payload->setChunkLength(B(100));
        payload->setTaskID(1);
        payload->setRsuID(1);
        payload->setVehicleID(1);
        EV_INFO << "**************************************" <<  endl;
        EV_INFO << "**************************************" <<  endl;
        EV_INFO << "After receiving Send packet: TaskAssignmentAckByEdge" << payload << endl;
        EV_INFO << "**************************************" <<  endl;
        EV_INFO << "**************************************" <<  endl;
        auto packet = createPacket("TaskAssignmentAckByEdge");

        packet->insertAtBack(payload);
        sendPacketToMECO(std::move(packet));
    }
    if(strcmp(pk->getName(),"CollectRequests")==0)
        {
        auto payload = makeShared<TaskCompletionMsgByEdge>();
        int rsuid = (pk->peekData<CollectRequests>())->getRsuID();
        timestampPayload(payload);
        payload->setChunkLength(B(100));
        payload->setTaskID(1);
        payload->setRsuID(rsuid);
        payload->setVehicleID(1);
        payload->setEdgeID(1);

        int c=0;
        for(int i=0; i<10000; i++){
            for(int j=0; j<10000; j++)
            {
                c++;
            }
        }

        payload->setResult("MyResult");

        EV_INFO << "**************************************" <<  endl;
        EV_INFO << "**************************************" <<  endl;
        EV_INFO << "After receiving Send packet: TaskCompletionMsgByEdge" << payload << endl;
        EV_INFO << "**************************************" <<  endl;
        EV_INFO << "**************************************" <<  endl;
        auto packet = createPacket("TaskCompletionMsgByEdge");

        packet->insertAtBack(payload);
        sendPacketToRSU(std::move(packet), rsuid);
        }
}
