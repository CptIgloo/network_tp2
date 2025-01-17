#include "game_object.hpp"
#include <string>
#include <iostream>

class Enemy : public GameObject
{
private:
    
    std::string type;

public:
    Enemy(){
        std::cout<<"Enemy created"<<std::endl;
    }
    REPLICATED(3,Enemy); 
    static const ReplicationClassID classID=0x03;  
    void setType(std::string newType);
    int Write(OutputStream& input) override;
    int Read(InputStream& input) override;
    void Destroy();
};