#include "game_object.hpp"
#include <string>
#include <iostream>


class Enemy : public GameObject
{
public: 
    Enemy(){ std::cout<<"Enemy created"<<std::endl;};
    float posX;
    float posY;
    float posZ;
    std::string type;
    float rotX;
    float rotY;
    float rotZ;
    float rotW;
    int Write(OutputStream& input);// override;
    int Read(InputStream& input);// override;
};