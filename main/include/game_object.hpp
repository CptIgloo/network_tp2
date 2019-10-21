#pragma once
#ifndef REPLICATIONCLASSID
#define REPLICATIONCLASSID
#include <cstdint>
#include "streams.hpp"

using ReplicationClassID = uint8_t;

#define REPLICATED(id,className)                                    \
enum : ReplicationClassID{mClassID = id};                           \
virtual ReplicationClassID ClassID() const  { return mClassID;}     \
static GameObject* CreateInstance() {return new className();}       \

class GameObject
{
public:
    static const ReplicationClassID classID=0x01; 
    //virtual void Destroy();
    virtual int Write(OutputStream &stream);
    virtual int Read(InputStream &stream);
};
#endif