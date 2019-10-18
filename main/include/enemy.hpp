#include "game_object.hpp"
#include <string>

class Enemy : public GameObject
{
public:
    float posX;
    float posY;
    float posZ;
    std::string type;
    float rotX;
    float rotY;
    float rotZ;
    float rotW;
    int Write(OutputStream& input) override;
    int Read(InputStream& input) override;
};