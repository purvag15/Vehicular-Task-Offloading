//
// Generated file, do not edit! Created by nedtool 5.6 from veins_inet/vfognetsim/rsuMessages/SendPacket.msg.
//

#ifndef __SENDPACKET_M_H
#define __SENDPACKET_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0506
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



class SendPacket;
#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/packet/chunk/Chunk_m.h" // import inet.common.packet.chunk.Chunk

/**
 * Class generated from <tt>veins_inet/vfognetsim/rsuMessages/SendPacket.msg:21</tt> by nedtool.
 * <pre>
 * //
 * // TODO generated message class
 * //
 * class SendPacket extends inet::FieldsChunk
 * {
 *     int vehicleID;
 *     int rsuId;
 * }
 * </pre>
 */
class SendPacket : public ::inet::FieldsChunk
{
  protected:
    int vehicleID = 0;
    int rsuId = 0;

  private:
    void copy(const SendPacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const SendPacket&);

  public:
    SendPacket();
    SendPacket(const SendPacket& other);
    virtual ~SendPacket();
    SendPacket& operator=(const SendPacket& other);
    virtual SendPacket *dup() const override {return new SendPacket(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getVehicleID() const;
    virtual void setVehicleID(int vehicleID);
    virtual int getRsuId() const;
    virtual void setRsuId(int rsuId);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const SendPacket& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, SendPacket& obj) {obj.parsimUnpack(b);}

#endif // ifndef __SENDPACKET_M_H

