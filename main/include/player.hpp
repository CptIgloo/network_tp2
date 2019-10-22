#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "game_object.hpp"
#include <string>

class Player : public GameObject
{
private:
    
    std::string name = "Todd";
    
public:
    REPLICATED(2,Player);

    int Write(OutputStream& input) override;
    int Read(InputStream& input) override;
    void Destroy();
};
#endif