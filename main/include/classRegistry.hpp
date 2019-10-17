#include "game_object.hpp"
#include <string>
#include <map>

class ClassRegistry 
{
    private:
        std::map<ReplicationClassID,std::function<GameObject(void)>> classRegister;
    public:
        GameObject Create(ReplicationClassID);
};