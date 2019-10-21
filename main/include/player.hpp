#include "game_object.hpp"
#include <string>

class Player : public GameObject
{
private:
    std::string nom;
    static const ReplicationClassID classID=0x02; 
public:
    int Write(OutputStream& input) override;
    int Read(InputStream& input) override;
};