#include "veins_inet/vfognetsim/vehicleMessages/VeinsInetAppTaskRequestByVehicle_1.h"
#include "inet/applications/vfognetsim/EdgeMessages/MIPSAdvertisementByEdge_m.h"
#include "inet/applications/vfognetsim/EdgeMessages/TaskAssignmentAckByEdge_m.h"
#include "inet/applications/vfognetsim/EdgeMessages/TaskCompletionMsgByEdge_m.h"

#include "inet/applications/vfognetsim/RSUMessages/MIPSAckByRSU_m.h"
#include "inet/applications/vfognetsim/RSUMessages/TaskAssignmentByRSU_m.h"
#include "inet/applications/vfognetsim/RSUMessages/TaskCompletionAckByRSU_m.h"
#include "inet/applications/vfognetsim/RSUMessages/TaskCompletionMsgByRSU_m.h"
#include "inet/applications/vfognetsim/RSUMessages/TaskRequestAckByRSU_m.h"

#include "inet/applications/vfognetsim/VehicleMessages/TaskCompletionAckByVehicle_m.h"
#include "inet/applications/vfognetsim/VehicleMessages/TaskRequestByVehicle_m.h"

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

Define_Module(VeinsInetAppTaskRequestByVehicle_1);

VeinsInetAppTaskRequestByVehicle_1::VeinsInetAppTaskRequestByVehicle_1()
{
}

bool VeinsInetAppTaskRequestByVehicle_1::startApplication()
{
    // host[0] should stop at t=20s
        //if (getParentModule()->getIndex() == 0) {
        auto callback = [this]() {
            //getParentModule()->getDisplayString().setTagArg("i", 1, "red");

            //traciVehicle->setSpeed(0);

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
    //}

    return true;
}

bool VeinsInetAppTaskRequestByVehicle_1::stopApplication()
{
    return true;
}

VeinsInetAppTaskRequestByVehicle_1::~VeinsInetAppTaskRequestByVehicle_1()
{
}

void VeinsInetAppTaskRequestByVehicle_1::processPacket(std::shared_ptr<inet::Packet> pk)
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
   // getParentModule()->getDisplayString().setTagArg("i", 1, "green");

    //traciVehicle->changeRoute(payload->getRoadId(), 999.9);

    //if (haveForwarded) return;

    //auto packet = createPacket("relay");
   // packet->insertAtBack(payload);
   // sendPacket(std::move(packet));

    //haveForwarded = true;
}

