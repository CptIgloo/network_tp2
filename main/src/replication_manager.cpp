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
    std::string received_string = stream.ReadStr();
    int size = received_string.size();
    std::byte* ptr = (std::byte*)received_string.c_str();
    std::vector<std::byte> received_bytes = std::vector<std::byte>(ptr,ptr + size);

    std::optional<std::vector<std::byte>> parsed_data_optional = PacketManager::parsePacket(received_bytes);

    if(parsed_data_optional.has_value())
    {
        std::vector<std::byte> data = parsed_data_optional.value();

        
    }
    else
    {
        std::cout<<"Bad packet formatting : ignoring packet"<<std::endl;
    }
}