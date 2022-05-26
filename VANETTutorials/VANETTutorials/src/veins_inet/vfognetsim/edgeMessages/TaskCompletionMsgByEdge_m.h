//
// Generated file, do not edit! Created by nedtool 5.6 from veins_inet/vfognetsim/edgeMessages/TaskCompletionMsgByEdge.msg.
//

#ifndef __TASKCOMPLETIONMSGBYEDGE_M_H
#define __TASKCOMPLETIONMSGBYEDGE_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0506
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



class TaskCompletionMsgByEdge;
#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/packet/chunk/Chunk_m.h" // import inet.common.packet.chunk.Chunk

/**
 * Class generated from <tt>veins_inet/vfognetsim/edgeMessages/TaskCompletionMsgByEdge.msg:26</tt> by nedtool.
 * <pre>
 * //
 * // Example message definition
 * //
 * class TaskCompletionMsgByEdge extends inet::FieldsChunk
 * {
 *     int taskID;
 *     int edgeID;
 *     int rsuID;
 *     int vehicleID;
 *     string result;
 * }
 * </pre>
 */
class TaskCompletionMsgByEdge : public ::inet::FieldsChunk
{
  protected:
    int taskID = 0;
    int edgeID = 0;
    int rsuID = 0;
    int vehicleID = 0;
    omnetpp::opp_string result;

  private:
    void copy(const TaskCompletionMsgByEdge& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const TaskCompletionMsgByEdge&);

  public:
    TaskCompletionMsgByEdge();
    TaskCompletionMsgByEdge(const TaskCompletionMsgByEdge& other);
    virtual ~TaskCompletionMsgByEdge();
    TaskCompletionMsgByEdge& operator=(const TaskCompletionMsgByEdge& other);
    virtual TaskCompletionMsgByEdge *dup() const override {return new TaskCompletionMsgByEdge(*this);}
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
    virtual const char * getResult() const;
    virtual void setResult(const char * result);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const TaskCompletionMsgByEdge& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, TaskCompletionMsgByEdge& obj) {obj.parsimUnpack(b);}

#endif // ifndef __TASKCOMPLETIONMSGBYEDGE_M_H
