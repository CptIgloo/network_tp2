#include "game_object.hpp"
#include <string>

class Player : public GameObject
{
public:
    float posX;
    float posY;
    float posZ;
    std::string nom;
    static const ReplicationClassID classID=0x02; 
    float rotX;
    float rotY;
    float rotZ;
    float rotW;
    int Write(OutputStream &stream) override;
    int Read(InputStream &stream) override;
};