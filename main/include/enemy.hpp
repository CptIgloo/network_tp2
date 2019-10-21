#include "game_object.hpp"
#include <string>

class Enemy : public GameObject
{
private:
     std::string type;

    float posX;
    float posY;
    float posZ;
    static const ReplicationClassID classID=0x03;  
    float rotX;
    float rotY; 
    float rotZ;
    float rotW;
public:
    int Write(OutputStream& input) override;
    int Read(InputStream& input) override;
};