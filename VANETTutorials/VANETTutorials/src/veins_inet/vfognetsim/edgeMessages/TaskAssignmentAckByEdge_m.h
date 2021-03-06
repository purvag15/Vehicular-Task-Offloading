//
// Generated file, do not edit! Created by nedtool 5.6 from veins_inet/vfognetsim/edgeMessages/TaskAssignmentAckByEdge.msg.
//

#ifndef __TASKASSIGNMENTACKBYEDGE_M_H
#define __TASKASSIGNMENTACKBYEDGE_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0506
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



class TaskAssignmentAckByEdge;
#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/packet/chunk/Chunk_m.h" // import inet.common.packet.chunk.Chunk

/**
 * Class generated from <tt>veins_inet/vfognetsim/edgeMessages/TaskAssignmentAckByEdge.msg:26</tt> by nedtool.
 * <pre>
 * //
 * // Example message definition
 * //
 * class TaskAssignmentAckByEdge extends inet::FieldsChunk
 * {
 *     int taskID;
 *     int edgeID;
 *     int rsuID;
 *     int vehicleID;
 * }
 * </pre>
 */
class TaskAssignmentAckByEdge : public ::inet::FieldsChunk
{
  protected:
    int taskID = 0;
    int edgeID = 0;
    int rsuID = 0;
    int vehicleID = 0;

  private:
    void copy(const TaskAssignmentAckByEdge& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const TaskAssignmentAckByEdge&);

  public:
    TaskAssignmentAckByEdge();
    TaskAssignmentAckByEdge(const TaskAssignmentAckByEdge& other);
    virtual ~TaskAssignmentAckByEdge();
    TaskAssignmentAckByEdge& operator=(const TaskAssignmentAckByEdge& other);
    virtual TaskAssignmentAckByEdge *dup() const override {return new TaskAssignmentAckByEdge(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getTaskID() const;
    virtual void setTaskID(int taskID);
    virtual int getEdgeID() const;
    virtual void setEdgeID(int edgeID);
    virtual int getRsuID() const;
    virtual void setRsuID(int rsuID);
    virtual int getVehicleID() const;
    virtual void setVehicleID(int vehicleID);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const TaskAssignmentAckByEdge& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, TaskAssignmentAckByEdge& obj) {obj.parsimUnpack(b);}

#endif // ifndef __TASKASSIGNMENTACKBYEDGE_M_H

