//
// Generated file, do not edit! Created by nedtool 5.6 from veins_inet/vfognetsim/rsuMessages/TaskCompletionAckByRSU.msg.
//

#ifndef __TASKCOMPLETIONACKBYRSU_M_H
#define __TASKCOMPLETIONACKBYRSU_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0506
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



class TaskCompletionAckByRSU;
#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/packet/chunk/Chunk_m.h" // import inet.common.packet.chunk.Chunk

/**
 * Class generated from <tt>veins_inet/vfognetsim/rsuMessages/TaskCompletionAckByRSU.msg:26</tt> by nedtool.
 * <pre>
 * //
 * // Example message definition
 * //
 * class TaskCompletionAckByRSU extends inet::FieldsChunk
 * {
 *     int rsuID;
 *     int edgeID;
 *     int taskID;
 *     int vehicleID;
 * }
 * </pre>
 */
class TaskCompletionAckByRSU : public ::inet::FieldsChunk
{
  protected:
    int rsuID = 0;
    int edgeID = 0;
    int taskID = 0;
    int vehicleID = 0;

  private:
    void copy(const TaskCompletionAckByRSU& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const TaskCompletionAckByRSU&);

  public:
    TaskCompletionAckByRSU();
    TaskCompletionAckByRSU(const TaskCompletionAckByRSU& other);
    virtual ~TaskCompletionAckByRSU();
    TaskCompletionAckByRSU& operator=(const TaskCompletionAckByRSU& other);
    virtual TaskCompletionAckByRSU *dup() const override {return new TaskCompletionAckByRSU(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getRsuID() const;
    virtual void setRsuID(int rsuID);
    virtual int getEdgeID() const;
    virtual void setEdgeID(int edgeID);
    virtual int getTaskID() const;
    virtual void setTaskID(int taskID);
    virtual int getVehicleID() const;
    virtual void setVehicleID(int vehicleID);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const TaskCompletionAckByRSU& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, TaskCompletionAckByRSU& obj) {obj.parsimUnpack(b);}

#endif // ifndef __TASKCOMPLETIONACKBYRSU_M_H
