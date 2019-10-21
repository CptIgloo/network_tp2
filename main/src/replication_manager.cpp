#include "replication_manager.hpp"
#include <cstddef>
#include <gsl/gsl>
#include <optional>
#include "classRegistry.hpp"
#include "linking_context.hpp"
#include <iostream>

//std::unordered_set<GameObject*> ReplicationManager::replicatedObjects = std::unordered_set<GameObject*>();

void ReplicationManager::Replicate(OutputStream stream,std::vector<GameObject*> objects)
{
    for(GameObject* gptr:objects){
        
       // stream.Write<uint16_t>(LinkingContext::getIdOfObject(gptr));
        gptr->Write(stream);
    }
}

void ReplicationManager::Replicate(InputStream stream)
{
    uint16_t networkID;
    ReplicationClassID classID;
    uint8_t taille;
    GameObject g;
    networkID=stream.Read<uint8_t>() << 8 | stream.Read<uint8_t>();

    
    if (LinkingContext::getObjectOfId(networkID).has_value()){
        
    }
    classID=stream.Read<ReplicationClassID>();
    if(classID<0||classID>3){
        std::cout<<"classID nous valable"<<std::endl;
        assert(EXIT_FAILURE);
    }
    taille=stream.Read<uint8_t>();
    g=ClassRegistry::getInstance().Create(classID);
    g.Read(stream);
    std::cout<<"Received "<<std::to_string(networkID)<<" "<<std::to_string(classID)<<" "<<std::to_string(taille)<<std::endl;

}