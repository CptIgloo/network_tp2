#pragma once

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
    GameObject() = default;
	virtual ~GameObject() = default;
    virtual void Destroy();
    virtual int Write(OutputStream& input);
    virtual int Read(InputStream& input);
    
    struct Transform {
        float pos_x;
        float pos_y;
        float pos_z;
    };
    struct Quaternion {
        float r_x;
        float r_y;
        float r_z;
        float r_w;
    };
   
protected : 
    Transform position;
    Quaternion rotation;
};  