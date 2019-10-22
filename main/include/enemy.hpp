#ifndef ENEMY_HPP
#define ENEMY_HPP
#include "game_object.hpp"
#include <string>
#include <iostream>

class Enemy : public GameObject
{
private:
    //On va limiter la taille 
    std::string type;

public:
    Enemy(){
        std::cout<<"Enemy created"<<std::endl;
    }
    static const ReplicationClassID classID=0x03;  
    int Write(OutputStream& input) override;
    int Read(InputStream& input) override;
    void Destroy();
};
#endif