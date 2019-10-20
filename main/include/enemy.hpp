#include "game_object.hpp"
#include <string>

class Enemy : public GameObject
{
public:
    float posX;
    float posY;
    float posZ;
    static const ReplicationClassID classID=0x03;  
    std::string type;
    float rotX;
    float rotY; 
    float rotZ;
    float rotW;
    int Write(OutputStream &stream) override;
    int Read(InputStream &stream) override;
    
};