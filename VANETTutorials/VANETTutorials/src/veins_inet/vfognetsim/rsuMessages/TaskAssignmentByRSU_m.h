//
// Generated file, do not edit! Created by nedtool 5.6 from veins_inet/vfognetsim/rsuMessages/TaskAssignmentByRSU.msg.
//

#ifndef __TASKASSIGNMENTBYRSU_M_H
#define __TASKASSIGNMENTBYRSU_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0506
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



class TaskAssignmentByRSU;
#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/packet/chunk/Chunk_m.h" // import inet.common.packet.chunk.Chunk

/**
 * Class generated from <tt>veins_inet/vfognetsim/rsuMessages/TaskAssignmentByRSU.msg:26</tt> by nedtool.
 * <pre>
 * //
 * // Example message definition
 * //
 * class TaskAssignmentByRSU extends inet::FieldsChunk
 * {
 *     int rsuID;
 *     int taskID;
 *     int vehicleID;
 *     int rq_MIPS;
 *     int taskSize;
 *     float delayTol;
 *     int x;
 *     int y;
 *     string filename;
 * }
 * </pre>
 */
class TaskAssignmentByRSU : public ::inet::FieldsChunk
{
  protected:
    int rsuID = 0;
    int taskID = 0;
    int vehicleID = 0;
    int rq_MIPS = 0;
    int taskSize = 0;
    float delayTol = 0;
    int x = 0;
    int y = 0;
    omnetpp::opp_string filename;

  private:
    void copy(const TaskAssignmentByRSU& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const TaskAssignmentByRSU&);

  public:
    TaskAssignmentByRSU();
    TaskAssignmentByRSU(const TaskAssignmentByRSU& other);
    virtual ~TaskAssignmentByRSU();
    TaskAssignmentByRSU& operator=(const TaskAssignmentByRSU& other);
    virtual TaskAssignmentByRSU *dup() const override {return new TaskAssignmentByRSU(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getRsuID() const;
    virtual void setRsuID(int rsuID);
    virtual int getTaskID() const;
    virtual void setTaskID(int taskID);
    virtual int getVehicleID() const;
    virtual void setVehicleID(int vehicleID);
    virtual int getRq_MIPS() const;
    virtual void setRq_MIPS(int rq_MIPS);
    virtual int getTaskSize() const;
    virtual void setTaskSize(int taskSize);
    virtual float getDelayTol() const;
    virtual void setDelayTol(float delayTol);
    virtual int getX() const;
    virtual void setX(int x);
    virtual int getY() const;
    virtual void setY(int y);
    virtual const char * getFilename() const;
    virtual void setFilename(const char * filename);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const TaskAssignmentByRSU& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, TaskAssignmentByRSU& obj) {obj.parsimUnpack(b);}

#endif // ifndef __TASKASSIGNMENTBYRSU_M_H
