#include <unordered_set>
#include "game_object.hpp"
#include <vector>

class ReplicationManager
{
    private :
        static std::unordered_set<std::shared_ptr<GameObject>> replicatedObjects;

    public :
        static void Replicate(InputStream &stream,std::vector<std::shared_ptr<GameObject>> objects);
        static void Replicate(OutputStream &stream);
};