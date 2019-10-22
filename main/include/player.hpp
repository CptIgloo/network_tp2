#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "game_object.hpp"
#include <string>

class Player : public GameObject
{
private:
    
    std::string name = "Todd";
    
public:
    static const ReplicationClassID classID=0x02; 
    int Write(OutputStream& input) override;
    int Read(InputStream& input) override;
    void Destroy();
};
#endif