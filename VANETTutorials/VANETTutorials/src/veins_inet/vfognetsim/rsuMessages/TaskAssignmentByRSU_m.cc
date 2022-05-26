//
// Generated file, do not edit! Created by nedtool 5.6 from veins_inet/vfognetsim/rsuMessages/TaskAssignmentByRSU.msg.
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
#include "TaskAssignmentByRSU_m.h"

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

Register_Class(TaskAssignmentByRSU)

TaskAssignmentByRSU::TaskAssignmentByRSU() : ::inet::FieldsChunk()
{
}

TaskAssignmentByRSU::TaskAssignmentByRSU(const TaskAssignmentByRSU& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

TaskAssignmentByRSU::~TaskAssignmentByRSU()
{
}

TaskAssignmentByRSU& TaskAssignmentByRSU::operator=(const TaskAssignmentByRSU& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void TaskAssignmentByRSU::copy(const TaskAssignmentByRSU& other)
{
    this->rsuID = other.rsuID;
    this->taskID = other.taskID;
    this->vehicleID = other.vehicleID;
    this->rq_MIPS = other.rq_MIPS;
    this->taskSize = other.taskSize;
    this->delayTol = other.delayTol;
    this->x = other.x;
    this->y = other.y;
    this->filename = other.filename;
}

void TaskAssignmentByRSU::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->rsuID);
    doParsimPacking(b,this->taskID);
    doParsimPacking(b,this->vehicleID);
    doParsimPacking(b,this->rq_MIPS);
    doParsimPacking(b,this->taskSize);
    doParsimPacking(b,this->delayTol);
    doParsimPacking(b,this->x);
    doParsimPacking(b,this->y);
    doParsimPacking(b,this->filename);
}

void TaskAssignmentByRSU::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->rsuID);
    doParsimUnpacking(b,this->taskID);
    doParsimUnpacking(b,this->vehicleID);
    doParsimUnpacking(b,this->rq_MIPS);
    doParsimUnpacking(b,this->taskSize);
    doParsimUnpacking(b,this->delayTol);
    doParsimUnpacking(b,this->x);
    doParsimUnpacking(b,this->y);
    doParsimUnpacking(b,this->filename);
}

int TaskAssignmentByRSU::getRsuID() const
{
    return this->rsuID;
}

void TaskAssignmentByRSU::setRsuID(int rsuID)
{
    handleChange();
    this->rsuID = rsuID;
}

int TaskAssignmentByRSU::getTaskID() const
{
    return this->taskID;
}

void TaskAssignmentByRSU::setTaskID(int taskID)
{
    handleChange();
    this->taskID = taskID;
}

int TaskAssignmentByRSU::getVehicleID() const
{
    return this->vehicleID;
}

void TaskAssignmentByRSU::setVehicleID(int vehicleID)
{
    handleChange();
    this->vehicleID = vehicleID;
}

int TaskAssignmentByRSU::getRq_MIPS() const
{
    return this->rq_MIPS;
}

void TaskAssignmentByRSU::setRq_MIPS(int rq_MIPS)
{
    handleChange();
    this->rq_MIPS = rq_MIPS;
}

int TaskAssignmentByRSU::getTaskSize() const
{
    return this->taskSize;
}

void TaskAssignmentByRSU::setTaskSize(int taskSize)
{
    handleChange();
    this->taskSize = taskSize;
}

float TaskAssignmentByRSU::getDelayTol() const
{
    return this->delayTol;
}

void TaskAssignmentByRSU::setDelayTol(float delayTol)
{
    handleChange();
    this->delayTol = delayTol;
}

int TaskAssignmentByRSU::getX() const
{
    return this->x;
}

void TaskAssignmentByRSU::setX(int x)
{
    handleChange();
    this->x = x;
}

int TaskAssignmentByRSU::getY() const
{
    return this->y;
}

void TaskAssignmentByRSU::setY(int y)
{
    handleChange();
    this->y = y;
}

const char * TaskAssignmentByRSU::getFilename() const
{
    return this->filename.c_str();
}

void TaskAssignmentByRSU::setFilename(const char * filename)
{
    handleChange();
    this->filename = filename;
}

class TaskAssignmentByRSUDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_rsuID,
        FIELD_taskID,
        FIELD_vehicleID,
        FIELD_rq_MIPS,
        FIELD_taskSize,
        FIELD_delayTol,
        FIELD_x,
        FIELD_y,
        FIELD_filename,
    };
  public:
    TaskAssignmentByRSUDescriptor();
    virtual ~TaskAssignmentByRSUDescriptor();

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

Register_ClassDescriptor(TaskAssignmentByRSUDescriptor)

TaskAssignmentByRSUDescriptor::TaskAssignmentByRSUDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(TaskAssignmentByRSU)), "inet::FieldsChunk")
{
    propertynames = nullptr;
}

TaskAssignmentByRSUDescriptor::~TaskAssignmentByRSUDescriptor()
{
    delete[] propertynames;
}

bool TaskAssignmentByRSUDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TaskAssignmentByRSU *>(obj)!=nullptr;
}

const char **TaskAssignmentByRSUDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *TaskAssignmentByRSUDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int TaskAssignmentByRSUDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 9+basedesc->getFieldCount() : 9;
}

unsigned int TaskAssignmentByRSUDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_rsuID
        FD_ISEDITABLE,    // FIELD_taskID
        FD_ISEDITABLE,    // FIELD_vehicleID
        FD_ISEDITABLE,    // FIELD_rq_MIPS
        FD_ISEDITABLE,    // FIELD_taskSize
        FD_ISEDITABLE,    // FIELD_delayTol
        FD_ISEDITABLE,    // FIELD_x
        FD_ISEDITABLE,    // FIELD_y
        FD_ISEDITABLE,    // FIELD_filename
    };
    return (field >= 0 && field < 9) ? fieldTypeFlags[field] : 0;
}

const char *TaskAssignmentByRSUDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "rsuID",
        "taskID",
        "vehicleID",
        "rq_MIPS",
        "taskSize",
        "delayTol",
        "x",
        "y",
        "filename",
    };
    return (field >= 0 && field < 9) ? fieldNames[field] : nullptr;
}

int TaskAssignmentByRSUDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'r' && strcmp(fieldName, "rsuID") == 0) return base+0;
    if (fieldName[0] == 't' && strcmp(fieldName, "taskID") == 0) return base+1;
    if (fieldName[0] == 'v' && strcmp(fieldName, "vehicleID") == 0) return base+2;
    if (fieldName[0] == 'r' && strcmp(fieldName, "rq_MIPS") == 0) return base+3;
    if (fieldName[0] == 't' && strcmp(fieldName, "taskSize") == 0) return base+4;
    if (fieldName[0] == 'd' && strcmp(fieldName, "delayTol") == 0) return base+5;
    if (fieldName[0] == 'x' && strcmp(fieldName, "x") == 0) return base+6;
    if (fieldName[0] == 'y' && strcmp(fieldName, "y") == 0) return base+7;
    if (fieldName[0] == 'f' && strcmp(fieldName, "filename") == 0) return base+8;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *TaskAssignmentByRSUDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_rsuID
        "int",    // FIELD_taskID
        "int",    // FIELD_vehicleID
        "int",    // FIELD_rq_MIPS
        "int",    // FIELD_taskSize
        "float",    // FIELD_delayTol
        "int",    // FIELD_x
        "int",    // FIELD_y
        "string",    // FIELD_filename
    };
    return (field >= 0 && field < 9) ? fieldTypeStrings[field] : nullptr;
}

const char **TaskAssignmentByRSUDescriptor::getFieldPropertyNames(int field) const
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

const char *TaskAssignmentByRSUDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int TaskAssignmentByRSUDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    TaskAssignmentByRSU *pp = (TaskAssignmentByRSU *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *TaskAssignmentByRSUDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    TaskAssignmentByRSU *pp = (TaskAssignmentByRSU *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TaskAssignmentByRSUDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    TaskAssignmentByRSU *pp = (TaskAssignmentByRSU *)object; (void)pp;
    switch (field) {
        case FIELD_rsuID: return long2string(pp->getRsuID());
        case FIELD_taskID: return long2string(pp->getTaskID());
        case FIELD_vehicleID: return long2string(pp->getVehicleID());
        case FIELD_rq_MIPS: return long2string(pp->getRq_MIPS());
        case FIELD_taskSize: return long2string(pp->getTaskSize());
        case FIELD_delayTol: return double2string(pp->getDelayTol());
        case FIELD_x: return long2string(pp->getX());
        case FIELD_y: return long2string(pp->getY());
        case FIELD_filename: return oppstring2string(pp->getFilename());
        default: return "";
    }
}

bool TaskAssignmentByRSUDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    TaskAssignmentByRSU *pp = (TaskAssignmentByRSU *)object; (void)pp;
    switch (field) {
        case FIELD_rsuID: pp->setRsuID(string2long(value)); return true;
        case FIELD_taskID: pp->setTaskID(string2long(value)); return true;
        case FIELD_vehicleID: pp->setVehicleID(string2long(value)); return true;
        case FIELD_rq_MIPS: pp->setRq_MIPS(string2long(value)); return true;
        case FIELD_taskSize: pp->setTaskSize(string2long(value)); return true;
        case FIELD_delayTol: pp->setDelayTol(string2double(value)); return true;
        case FIELD_x: pp->setX(string2long(value)); return true;
        case FIELD_y: pp->setY(string2long(value)); return true;
        case FIELD_filename: pp->setFilename((value)); return true;
        default: return false;
    }
}

const char *TaskAssignmentByRSUDescriptor::getFieldStructName(int field) const
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

void *TaskAssignmentByRSUDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    TaskAssignmentByRSU *pp = (TaskAssignmentByRSU *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

