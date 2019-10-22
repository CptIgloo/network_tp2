#include "game_object.hpp"
#include <string>

class Player : public GameObject
{
private:
    
    std::string name;
    
public:
    REPLICATED(2,Player);
    int Write(OutputStream& input) override;
    int Read(InputStream& input) override;
};