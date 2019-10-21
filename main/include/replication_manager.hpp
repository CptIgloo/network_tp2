#include <unordered_set>
#include "game_object.hpp"
#include <vector>

class ReplicationManager
{
    private :
        static std::unordered_set<GameObject*> replicatedObjects;

    public :
        static void Replicate(OutputStream stream,std::vector<GameObject*> objects);
        static void Replicate(InputStream stream);
};