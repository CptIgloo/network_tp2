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
    std::array<uint8_t,4> header={(uint8_t)'C',(uint8_t)'O',(uint8_t)'D',(uint8_t)'E'};
    stream.Write<uint8_t>(header[0]);stream.Write<uint8_t>(header[1]);stream.Write<uint8_t>(header[2]);stream.Write<uint8_t>(header[3]);
    uint8_t nul =(uint8_t)PacketType::Sync;
    stream.Write<uint8_t>(nul);
    for(GameObject* gptr:objects){
        auto id_Obj= LinkingContext::getIdOfObject(gptr);
        if(id_Obj.has_value()){
            stream.Write<NetworkID>(id_Obj.value());
            ReplicationClassID r_id = gptr->ClassID();
            stream.Write<ReplicationClassID>(r_id);
            //Donner une vraie valeur à la taille
            nul=18;
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
    
    auto str = stream.Read(4);
    std::string header;
    std::transform(str.begin(), str.end(), std::back_inserter(header), [](std::byte b) { return (char)b; });

   
    std::cout<<header<<std::endl;
    if (header.compare("CODE")!=0){
        return;
    }
    std::unordered_set<GameObject*> objectRemaining=this->replicatedObjects;
    uint8_t packetType=stream.Read<uint8_t>();
    if(packetType==(uint8_t)PacketType::Sync){
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
    else 
    {
        std::cout<<"Message du mauvais type"<<std::endl;
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