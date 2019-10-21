#include "game_object.hpp"
#include <string>

class Enemy : public GameObject
{
private:
    static const ReplicationClassID classID=0x03;  
    std::string type;

public:
    int Write(OutputStream& input) override;
    int Read(InputStream& input) override;
};