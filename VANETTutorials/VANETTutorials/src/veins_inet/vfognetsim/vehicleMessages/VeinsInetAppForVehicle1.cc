#include "veins_inet/vfognetsim/vehicleMessages/VeinsInetAppForVehicle1.h"

#include "veins_inet/vfognetsim/edgeMessages/MIPSAdvertisementByEdge_m.h"
#include "veins_inet/vfognetsim/edgeMessages/TaskAssignmentAckByEdge_m.h"
#include "veins_inet/vfognetsim/edgeMessages/TaskCompletionMsgByEdge_m.h"

#include "veins_inet/vfognetsim/rsuMessages/MIPSAckByRSU_m.h"
#include "veins_inet/vfognetsim/rsuMessages/TaskAssignmentByRSU_m.h"
#include "veins_inet/vfognetsim/rsuMessages/TaskCompletionAckByRSU_m.h"
#include "veins_inet/vfognetsim/rsuMessages/TaskCompletionMsgByRSU_m.h"
#include "veins_inet/vfognetsim/rsuMessages/TaskRequestAckByRSU_m.h"

#include "veins_inet/vfognetsim/vehicleMessages/TaskCompletionAckByVehicle_m.h"
#include "veins_inet/vfognetsim/rsuMessages/SendPacket_m.h"
#include "veins_inet/vfognetsim/vehicleMessages/TaskRequestByVehicle_m.h"

#include "inet/common/ModuleAccess.h"
#include "inet/common/packet/Packet.h"
#include "inet/common/TagBase_m.h"
#include "inet/common/TimeTag_m.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/networklayer/common/L3AddressTag_m.h"
#include "inet/transportlayer/contract/udp/UdpControlInfo_m.h"
#include<string>

using namespace inet;

Define_Module(VeinsInetAppForVehicle1);

VeinsInetAppForVehicle1::VeinsInetAppForVehicle1()
{
}

bool VeinsInetAppForVehicle1::startApplication()
{
    auto callback = [this]()
    {
        auto payload = makeShared<TaskRequestByVehicle>();
        timestampPayload(payload);
        payload->setChunkLength(B(100));
        payload->setTaskID(1);

        int taskSize = 10*(rand()%100 + 1);
        float MIPS = 0.1*(rand()%100 + 1)+1;
        int delay = 20*(rand()%100 + 1);

        payload->setRq_MIPS(MIPS);
        payload->setVehicleID(getIndex());
        std::cout<<getIndex()<<" My Index \n";

        payload->setTaskSize(taskSize);
        payload->setDelayTol(delay);
        payload->setX((mobility->getCurrentPosition()).x);
        payload->setY((mobility->getCurrentPosition()).y);

        EV_INFO << "**************************************" <<  endl;
        EV_INFO << "**************************************" <<  endl;
        EV_INFO << "Send packet: TaskRequestByVehicle" << payload << endl;
        EV_INFO << "**************************************" <<  endl;
        EV_INFO << getIndex() <<  endl;
        auto packet = createPacket("TaskRequestByVehicle");

        packet->insertAtBack(payload);
        sendPacketToRSU(std::move(packet));
    };
    timerManager.create(veins::TimerSpecification(callback).oneshotAt(SimTime(20, SIMTIME_S)));
    return true;
}

bool VeinsInetAppForVehicle1::stopApplication()
{
    return true;
}

VeinsInetAppForVehicle1::~VeinsInetAppForVehicle1()
{
}

void VeinsInetAppForVehicle1::processPacket(std::shared_ptr<inet::Packet> pk)
{
    if(strcmp(pk->getName(),"TaskCompletionMsgByRSU")==0)
    {
        auto payload = makeShared<TaskCompletionAckByVehicle>();
        timestampPayload(payload);
        payload->setChunkLength(B(100));
        payload->setRsuID((pk->peekData<TaskCompletionMsgByRSU>())->getRsuID());
        payload->setTaskID((pk->peekData<TaskCompletionMsgByRSU>())->getTaskID());
        payload->setVehicleID((pk->peekData<TaskCompletionMsgByRSU>())->getVehicleID());
        EV_INFO << "**************************************" <<  endl;
        EV_INFO << "**************************************" <<  endl;
        EV_INFO << "RSU Send packet: TaskCompletionAckByVehicle" << payload << endl;
        EV_INFO << "**************************************" <<  endl;
        EV_INFO << "**************************************" <<  endl;
        auto packet = createPacket("TaskCompletionAckByVehicle");

        packet->insertAtBack(payload);
        sendPacketToRSU(std::move(packet));
    }

    if(strcmp(pk->getName(),"SendPacket")==0)
    {
        auto payload = makeShared<TaskRequestByVehicle>();
        timestampPayload(payload);
        payload->setChunkLength(B(100));
        payload->setTaskID(1);

        int taskSize = 10*(rand()%100 + 1);
        float MIPS = 0.1*(rand()%100 + 1);
        int delay = 20*(rand()%100 + 1);

        payload->setRq_MIPS(MIPS);
//        payload->setVehicleID((pk->peekData<SendPacket>())->getVehicleID());
        payload->setTaskSize(taskSize);
        payload->setDelayTol(delay);
        payload->setX((mobility->getCurrentPosition()).x);
        payload->setY((mobility->getCurrentPosition()).y);

        EV_INFO << "**************************************" <<  endl;
        EV_INFO << "**************************************" <<  endl;
        EV_INFO << "Send packet: TaskRequestByVehicle" << payload << endl;
        EV_INFO << "**************************************" <<  endl;
        EV_INFO << getIndex() <<  endl;
        auto packet = createPacket("TaskRequestByVehicle");

        packet->insertAtBack(payload);
        sendPacketToRSU(std::move(packet));
    }
}

