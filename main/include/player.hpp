#include "game_object.hpp"
#include <string>

class Player : public GameObject
{
private:
    static const ReplicationClassID classID=0x02; 
    std::string name;
    
public:
    int Write(OutputStream& input) override;
    int Read(InputStream& input) override;
    void Destroy();
};