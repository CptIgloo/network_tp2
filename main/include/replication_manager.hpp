#include <unordered_set>
#include "game_object.hpp"
#include <vector>

enum class PacketType : uint8_t
{
    Hello = 0x00,
    Sync = 0x01,
    Bye = 0x02,
    PacketType_Max
};

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