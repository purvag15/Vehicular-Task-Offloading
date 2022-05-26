//
// Generated file, do not edit! Created by nedtool 5.6 from veins_inet/vfognetsim/edgeMessages/TaskAssignmentAckByEdge.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include "TaskAssignmentAckByEdge_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

namespace {
template <class T> inline
typename std::enable_if<std::is_polymorphic<T>::value && std::is_base_of<omnetpp::cObject,T>::value, void *>::type
toVoidPtr(T* t)
{
    return (void *)(static_cast<const omnetpp::cObject *>(t));
}

template <class T> inline
typename std::enable_if<std::is_polymorphic<T>::value && !std::is_base_of<omnetpp::cObject,T>::value, void *>::type
toVoidPtr(T* t)
{
    return (void *)dynamic_cast<const void *>(t);
}

template <class T> inline
typename std::enable_if<!std::is_polymorphic<T>::value, void *>::type
toVoidPtr(T* t)
{
    return (void *)static_cast<const void *>(t);
}

}


// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule to generate operator<< for shared_ptr<T>
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const std::shared_ptr<T>& t) { return out << t.get(); }

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');

    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

Register_Class(TaskAssignmentAckByEdge)

TaskAssignmentAckByEdge::TaskAssignmentAckByEdge() : ::inet::FieldsChunk()
{
}

TaskAssignmentAckByEdge::TaskAssignmentAckByEdge(const TaskAssignmentAckByEdge& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

TaskAssignmentAckByEdge::~TaskAssignmentAckByEdge()
{
}

TaskAssignmentAckByEdge& TaskAssignmentAckByEdge::operator=(const TaskAssignmentAckByEdge& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void TaskAssignmentAckByEdge::copy(const TaskAssignmentAckByEdge& other)
{
    this->taskID = other.taskID;
    this->edgeID = other.edgeID;
    this->rsuID = other.rsuID;
    this->vehicleID = other.vehicleID;
}

void TaskAssignmentAckByEdge::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->taskID);
    doParsimPacking(b,this->edgeID);
    doParsimPacking(b,this->rsuID);
    doParsimPacking(b,this->vehicleID);
}

void TaskAssignmentAckByEdge::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->taskID);
    doParsimUnpacking(b,this->edgeID);
    doParsimUnpacking(b,this->rsuID);
    doParsimUnpacking(b,this->vehicleID);
}

int TaskAssignmentAckByEdge::getTaskID() const
{
    return this->taskID;
}

void TaskAssignmentAckByEdge::setTaskID(int taskID)
{
    handleChange();
    this->taskID = taskID;
}

int TaskAssignmentAckByEdge::getEdgeID() const
{
    return this->edgeID;
}

void TaskAssignmentAckByEdge::setEdgeID(int edgeID)
{
    handleChange();
    this->edgeID = edgeID;
}

int TaskAssignmentAckByEdge::getRsuID() const
{
    return this->rsuID;
}

void TaskAssignmentAckByEdge::setRsuID(int rsuID)
{
    handleChange();
    this->rsuID = rsuID;
}

int TaskAssignmentAckByEdge::getVehicleID() const
{
    return this->vehicleID;
}

void TaskAssignmentAckByEdge::setVehicleID(int vehicleID)
{
    handleChange();
    this->vehicleID = vehicleID;
}

class TaskAssignmentAckByEdgeDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_taskID,
        FIELD_edgeID,
        FIELD_rsuID,
        FIELD_vehicleID,
    };
  public:
    TaskAssignmentAckByEdgeDescriptor();
    virtual ~TaskAssignmentAckByEdgeDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(TaskAssignmentAckByEdgeDescriptor)

TaskAssignmentAckByEdgeDescriptor::TaskAssignmentAckByEdgeDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(TaskAssignmentAckByEdge)), "inet::FieldsChunk")
{
    propertynames = nullptr;
}

TaskAssignmentAckByEdgeDescriptor::~TaskAssignmentAckByEdgeDescriptor()
{
    delete[] propertynames;
}

bool TaskAssignmentAckByEdgeDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TaskAssignmentAckByEdge *>(obj)!=nullptr;
}

const char **TaskAssignmentAckByEdgeDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *TaskAssignmentAckByEdgeDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int TaskAssignmentAckByEdgeDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount() : 4;
}

unsigned int TaskAssignmentAckByEdgeDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_taskID
        FD_ISEDITABLE,    // FIELD_edgeID
        FD_ISEDITABLE,    // FIELD_rsuID
        FD_ISEDITABLE,    // FIELD_vehicleID
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *TaskAssignmentAckByEdgeDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "taskID",
        "edgeID",
        "rsuID",
        "vehicleID",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int TaskAssignmentAckByEdgeDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 't' && strcmp(fieldName, "taskID") == 0) return base+0;
    if (fieldName[0] == 'e' && strcmp(fieldName, "edgeID") == 0) return base+1;
    if (fieldName[0] == 'r' && strcmp(fieldName, "rsuID") == 0) return base+2;
    if (fieldName[0] == 'v' && strcmp(fieldName, "vehicleID") == 0) return base+3;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *TaskAssignmentAckByEdgeDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_taskID
        "int",    // FIELD_edgeID
        "int",    // FIELD_rsuID
        "int",    // FIELD_vehicleID
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **TaskAssignmentAckByEdgeDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *TaskAssignmentAckByEdgeDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int TaskAssignmentAckByEdgeDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    TaskAssignmentAckByEdge *pp = (TaskAssignmentAckByEdge *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *TaskAssignmentAckByEdgeDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    TaskAssignmentAckByEdge *pp = (TaskAssignmentAckByEdge *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TaskAssignmentAckByEdgeDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    TaskAssignmentAckByEdge *pp = (TaskAssignmentAckByEdge *)object; (void)pp;
    switch (field) {
        case FIELD_taskID: return long2string(pp->getTaskID());
        case FIELD_edgeID: return long2string(pp->getEdgeID());
        case FIELD_rsuID: return long2string(pp->getRsuID());
        case FIELD_vehicleID: return long2string(pp->getVehicleID());
        default: return "";
    }
}

bool TaskAssignmentAckByEdgeDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    TaskAssignmentAckByEdge *pp = (TaskAssignmentAckByEdge *)object; (void)pp;
    switch (field) {
        case FIELD_taskID: pp->setTaskID(string2long(value)); return true;
        case FIELD_edgeID: pp->setEdgeID(string2long(value)); return true;
        case FIELD_rsuID: pp->setRsuID(string2long(value)); return true;
        case FIELD_vehicleID: pp->setVehicleID(string2long(value)); return true;
        default: return false;
    }
}

const char *TaskAssignmentAckByEdgeDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *TaskAssignmentAckByEdgeDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    TaskAssignmentAckByEdge *pp = (TaskAssignmentAckByEdge *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

