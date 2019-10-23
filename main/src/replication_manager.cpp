#include "replication_manager.hpp"
#include <cstddef>
#include <gsl/gsl>
#include <optional>
#include "classRegistry.hpp"
#include "linking_context.hpp"
#include <iostream>

//std::unordered_set<GameObject*> ReplicationManager::replicatedObjects = std::unordered_set<GameObject*>();

void ReplicationManager::Replicate(OutputStream& stream,std::vector<GameObject*> objects)
{
    for(GameObject* gptr:objects){
        auto id_Obj= LinkingContext::getIdOfObject(gptr);
        if(id_Obj.has_value()){
            stream.Write<NetworkID>(id_Obj.value());
            ReplicationClassID r_id = gptr->ClassID();
            stream.Write<ReplicationClassID>(r_id);
            //Donner une vraie valeur à la taille
            uint8_t nul=18;
            stream.Write<uint8_t>(nul);
            gptr->Write(stream);
            std::cout<<"Object written"<<std::endl;
        }
        else{
            std::cout<<"Object does not exist in context"<<std::endl;
        }
    }
}

void ReplicationManager::Replicate(InputStream& stream)
{
    std::unordered_set<GameObject*> objectRemaining=this->replicatedObjects;
    while(stream.RemainingSize()>=18){
        objectRemaining.erase(this->readOneGameObject(stream));
        while (stream.RemainingSize()%18!=0)
        {
            stream.Read<uint8_t>();
        }

    }
    for(GameObject* toRemove:objectRemaining){
        this->replicatedObjects.erase(toRemove);
    }
}

GameObject* ReplicationManager::readOneGameObject(InputStream& stream){
    NetworkID networkID;
    ReplicationClassID classID;
    uint8_t taille;
    
    networkID=stream.Read<NetworkID>();

    std::optional<GameObject*> gptr=LinkingContext::getObjectOfId(networkID);

    classID=stream.Read<ReplicationClassID>();
    if(classID<1||classID>3){
            std::cout<<"classID not valid"<<std::endl;
            return {};
    }
    taille=stream.Read<uint8_t>();
    
    //If the GameObject is in the linkingContext but not in the set, we add it.
    if (gptr.has_value()){
        if(this->replicatedObjects.find(gptr.value())==this->replicatedObjects.end()){
            this->replicatedObjects.insert(gptr.value());
        }
        gptr.value()->Read(stream);
        std::cout<<"Received "<<std::to_string(networkID)<<" "<<std::to_string(classID)<<" "<<std::to_string(taille)<<std::endl; 
        return gptr.value();
    }
    else{
        std::cout<<"New object created"<<std::endl;
        GameObject* g=ClassRegistry::getInstance().Create(classID);
        g->Read(stream);
        this->replicatedObjects.insert(g);
        LinkingContext::addToContext(g);
        std::cout<<"Received "<<std::to_string(networkID)<<" "<<std::to_string(classID)<<" "<<std::to_string(taille)<<std::endl; 
        return g;
    }
}