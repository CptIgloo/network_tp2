#include <unordered_set>
#include "game_object.hpp"
#include <vector>

class ReplicationManager
{
    private :
        std::unordered_set<GameObject*> replicatedObjects;

    public :
        void Replicate(MemoryStream stream,std::vector<GameObject*> objects);
        void Replicate(MemoryStream stream);
};