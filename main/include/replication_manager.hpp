#include <unordered_set>
#include "game_object.hpp"
#include <vector>

class ReplicationManager
{
    private :
        std::unordered_set<GameObject*> replicatedObjects;
        GameObject* readOneGameObject(InputStream& stream);
    public :
        static ReplicationManager& getInstance(){
            static ReplicationManager instance;
            return instance;
            
        }
       
        void Replicate(OutputStream& stream,std::vector<GameObject*> objects);
        void Replicate(InputStream& stream);
};