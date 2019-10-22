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
        auto id_Obj= LinkingContext::getIdOfObject(gptr);
        if(id_Obj.has_value()){
            stream.Write<uint16_t>(id_Obj.value());
            gptr->Write(stream);
        }
        else{
            std::cout<<"Object does not exist in context"<<std::endl;
        }
    }
}

void ReplicationManager::Replicate(InputStream stream)
{
    uint16_t networkID;
    ReplicationClassID classID;
    uint8_t taille;
    
    networkID=stream.Read<uint8_t>() << 8 | stream.Read<uint8_t>();

    std::optional<GameObject*> gptr=LinkingContext::getObjectOfId(networkID);
    
    classID=stream.Read<ReplicationClassID>();
    if(classID<0||classID>3){
            std::cout<<"classID not valid"<<std::endl;
            assert(EXIT_FAILURE);
    }
    taille=stream.Read<uint8_t>();
    
    //If the GameObject is in the linkingContext but not in the set, we add it.
    if (gptr.has_value()&&this->replicatedObjects.find(gptr.value())==this->replicatedObjects.end()){
        this->replicatedObjects.insert(gptr.value());
        gptr.value()->Read(stream);
    }
    else{
        std::cout<<"New object created"<<std::endl;
        GameObject g=ClassRegistry::getInstance().Create(classID);
        g.Read(stream);
        this->replicatedObjects.insert(&g);
    }
   
    std::cout<<"Received "<<std::to_string(networkID)<<" "<<std::to_string(classID)<<" "<<std::to_string(taille)<<std::endl;
    
}