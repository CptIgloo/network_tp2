#include "replication_manager.hpp"
#include <cstddef>
#include <gsl/gsl>
#include "packet_manager.hpp"
#include "classRegistry.hpp"
#include <optional>
#include <iostream>

std::unordered_set<GameObject*> ReplicationManager::replicatedObjects = std::unordered_set<GameObject*>();

void ReplicationManager::Replicate(InputStream &stream,std::vector<GameObject*> objects)
{
    stream.Flush();
    PacketManager::createReplicationPacket(objects,stream);
}

void ReplicationManager::Replicate(OutputStream &stream)
{
    std::optional<OutputStream> parsed_data_optional = PacketManager::parsePacket(stream);

    if(parsed_data_optional.has_value())
    {
        OutputStream data = parsed_data_optional.value();
        std::unordered_set<GameObject*> objects_received = std::unordered_set<GameObject*>();
        while(data.RemainingSize() > 0)
        {
            NetworkID n_id = data.Read<NetworkID>();
            ReplicationClassID c_id = data.Read<ReplicationClassID>();
            uint8_t object_size = data.Read<uint8_t>();

            gsl::span<std::byte> object_data = data.Read(object_size);
            InputStream stream_to_object = InputStream(object_data);

            std::optional<GameObject*> object_pointer_optional = LinkingContext::getObjectOfId(n_id);

            //Objet connu dans le contexte
            if(object_pointer_optional.has_value())
            {
                GameObject* object = object_pointer_optional.value();
                
                if(object->classID == c_id)
                {
                    object->Read(stream_to_object);
                    objects_received.insert(object);
                }
            }
            else
            {
                //Objet inconnu au contexte
                GameObject object = ClassRegistry::getInstance().Create(c_id);
            }
            
        }
        //N_ID (2) - C_ID (1) - SIZE (1) - DATA
    }
    else
    {
        std::cout<<"Bad packet formatting : ignoring packet"<<std::endl;
    }
}