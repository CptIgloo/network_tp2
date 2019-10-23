#pragma once
#include <cstdint>
#include "streams.hpp"

using ReplicationClassID = uint8_t;

struct Transform 
{
    float pos_x;
    float pos_y;
    float pos_z;
};

struct Quaternion 
{
    float r_x;
    float r_y;
    float r_z;
    float r_w;
};

#define REPLICATED(id,className)                                    \
enum : ReplicationClassID{mClassID = id};                           \
virtual ReplicationClassID ClassID() const  { return mClassID;}     \
static std::shared_ptr<className> CreateInstance() {return std::make_shared<className>(className());}       \

class GameObject
{
    public:
        REPLICATED(1,GameObject);
        
        GameObject() = default;
        virtual ~GameObject() = default;
        virtual void Destroy();
        virtual int Write(OutputStream& input);
        virtual int Read(InputStream& input);
    
    protected : 
        Transform position;
        Quaternion rotation;
};  
