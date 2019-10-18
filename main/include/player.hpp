#include "game_object.hpp"
#include <string>

class Player : public GameObject
{
public:
    float posX;
    float posY;
    float posZ;
    std::string nom;
    float rotX;
    float rotY;
    float rotZ;
    float rotW;

    int Write(OutputStream& input); //override;
    int Read(InputStream& input);// override;
};