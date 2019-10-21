#include "replication_manager.hpp"
#include <cstddef>
#include <gsl/gsl>
#include "packet_manager.hpp"
#include <optional>
#include "classRegistry.hpp"
#include <iostream>

//std::unordered_set<GameObject*> ReplicationManager::replicatedObjects = std::unordered_set<GameObject*>();

void ReplicationManager::Replicate(OutputStream stream,std::vector<GameObject*> objects)
{
}

void ReplicationManager::Replicate(InputStream stream)
{
    std::byte b=stream.Read();
    std::string received_string = stream.ReadStr();
    int size = received_string.size();
    std::byte* ptr = (std::byte*)received_string.c_str();
    std::vector<std::byte> received_bytes = std::vector<std::byte>(ptr,ptr + size);

    std::optional<std::vector<std::byte>> parsed_data_optional = PacketManager::parsePacket(received_bytes);
    
    if(parsed_data_optional.has_value())
    {
        uint16_t networkID;
        ReplicationClassID classID;
        uint8_t taille;
        GameObject g;

        std::vector<std::byte> data = parsed_data_optional.value();
        networkID=(uint16_t)(data.front() << 8 | data.at(1));
        classID=(ReplicationClassID)data.at(2);
        taille=(uint8_t)data.at(3);
        g=ClassRegistry::getInstance().Create(classID);
        //g.Read();
    }
    else
    {
        std::cout<<"Bad packet formatting : ignoring packet"<<std::endl;
    }
}