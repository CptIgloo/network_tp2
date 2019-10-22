#include "replication_manager.hpp"
#include <cstddef>
#include <gsl/gsl>
#include "packet_manager.hpp"
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
    }
    else
    {
        std::cout<<"Bad packet formatting : ignoring packet"<<std::endl;
    }
}