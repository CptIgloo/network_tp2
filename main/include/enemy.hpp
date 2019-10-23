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
    REPLICATED(3,Enemy); 
    int Write(OutputStream& input) override;
    int Read(InputStream& input) override;
    void Destroy() override;
};
#endif