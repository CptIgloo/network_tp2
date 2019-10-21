#include "replication_manager.hpp"
#include <cstddef>
#include <gsl/gsl>
#include <optional>
#include "classRegistry.hpp"
#include <iostream>

//std::unordered_set<GameObject*> ReplicationManager::replicatedObjects = std::unordered_set<GameObject*>();

void ReplicationManager::Replicate(OutputStream stream,std::vector<GameObject*> objects)
{
}

void ReplicationManager::Replicate(InputStream stream)
{
    uint16_t networkID;
    ReplicationClassID classID;
    uint8_t taille;
    GameObject g;

    networkID=stream.Read<uint16_t>();;
    classID=stream.Read<ReplicationClassID>();
    taille=stream.Read<uint8_t>();
    g=ClassRegistry::getInstance().Create(classID);
    g.Read(stream);
    std::cout<<"Received "<<std::to_string(networkID)<<" "<<std::to_string(classID)<<" "<<std::to_string(taille)<<std::endl;

}