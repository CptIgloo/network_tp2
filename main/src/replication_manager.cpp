#include "replication_manager.hpp"
#include <cstddef>
#include <gsl/gsl>
#include "packet_manager.hpp"
#include "classRegistry.hpp"
#include <optional>
#include <iostream>
#include <algorithm>

std::unordered_set<std::shared_ptr<GameObject>> ReplicationManager::replicatedObjects = std::unordered_set<std::shared_ptr<GameObject>>();

void ReplicationManager::Replicate(InputStream &stream,std::vector<std::shared_ptr<GameObject>> objects)
{
    stream.Flush();
    PacketManager::createReplicationPacket(objects,stream);
}

void ReplicationManager::Replicate(OutputStream &stream)
{
    std::optional<OutputStream> parsed_data_optional = PacketManager::parsePacketAndGetData(stream);

    if(parsed_data_optional.has_value())
    {
        OutputStream data = parsed_data_optional.value();
        std::unordered_set<std::shared_ptr<GameObject>> objects_received = std::unordered_set<std::shared_ptr<GameObject>>();
        //N_ID (2) - C_ID (1) - SIZE (1) - DATA
        while(data.RemainingSize() > 0)
        {
            NetworkID n_id = data.Read<NetworkID>();
            ReplicationClassID c_id = data.Read<ReplicationClassID>();
            uint8_t object_size = data.Read<uint8_t>();

            gsl::span<std::byte> object_data = data.Read(object_size);
            InputStream stream_to_object = InputStream(object_data);

            std::optional<std::shared_ptr<GameObject>> object_pointer_optional = LinkingContext::getObjectOfId(n_id);

            //Objet connu dans le contexte
            if(object_pointer_optional.has_value())
            {
                std::shared_ptr<GameObject> object = object_pointer_optional.value();
                
                if(object->ClassID() == c_id)
                {
                    object->Read(stream_to_object);
                    objects_received.insert(object);
                }
            }
            else
            {
                //Objet inconnu au contexte
                std::optional<std::shared_ptr<GameObject>> object_optional = ClassRegistry::getInstance().Create(c_id);
                if(object_optional.has_value())
                {
                    std::shared_ptr<GameObject> object = object_optional.value();
                    object->Read(stream_to_object);
                    objects_received.insert(object);
                    replicatedObjects.insert(object);
                    LinkingContext::addToContext(object);
                }
                else
                {
                    std::cout<<"Invalid class id : ignoring object"<<std::endl;
                }
            }
        }
       
        //Vérification et suprresion des objects qui n'existent plus
        std::unordered_set<std::shared_ptr<GameObject>>::iterator it = replicatedObjects.begin();

        while (it != replicatedObjects.end())
        {
            auto curr = it++;
            if (objects_received.find(*curr) != objects_received.end()) {
                replicatedObjects.erase(curr);
            }
        }

        /* J'aurais bien aimé faire ca mais ca compile pas
        auto end = std::remove_if(replicatedObjects.begin(),
							replicatedObjects.end(),
							[objects_received](std::shared_ptr<GameObject> it) {
								return objects_received.find(it) != objects_received.end();
							});
        */
    }
    else
    {
        std::cout<<"Bad packet formatting : ignoring packet"<<std::endl;
    }
}