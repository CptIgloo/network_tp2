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
    //Temp is only a temporary container for the next function because it doesn't want a casted value directly
    uint8_t temp =(uint8_t)PacketType::Sync;
    stream.Write<uint8_t>(temp);

    OutputStream tempOutputStream;

    for(GameObject* gptr:objects){
        tempOutputStream.Flush();

        auto id_Obj= LinkingContext::getIdOfObject(gptr);
        if(id_Obj.has_value()){
            stream.Write<NetworkID>(id_Obj.value());
            ReplicationClassID r_id = gptr->ClassID();
            stream.Write<ReplicationClassID>(r_id);
            
            gptr->Write(tempOutputStream);
            
            temp=tempOutputStream.Size();
            stream.Write<uint8_t>(temp);
            
            stream.Write(tempOutputStream.Data());
            std::cout<<"Object written"<<std::endl;
        }
        else{
            std::cout<<"Object does not exist in context"<<std::endl;
        }
    }
}

void ReplicationManager::Replicate(InputStream& stream)
{
    uint8_t originalSize;
    uint8_t size;
    auto str = stream.Read(4);
    std::cout<<"New packet received"<<std::endl;
    std::string header;
    std::transform(str.begin(), str.end(), std::back_inserter(header), [](std::byte b) { return (char)b; });
    std::cout<<header<<std::endl;
    if (header.compare("CODE")!=0){
        return;
    }
    std::unordered_set<GameObject*> objectRemaining=this->replicatedObjects;
    uint8_t packetType=stream.Read<uint8_t>();
     std::cout<<"Packet type: "<<std::to_string(packetType)<<std::endl;
    if(packetType==(uint8_t)PacketType::Sync){
        while(stream.RemainingSize()>=18){
            originalSize=stream.RemainingSize();
            size=0;
            objectRemaining.erase(this->readOneGameObject(stream,size));
            
            while (stream.RemainingSize()%(size+4)!=0)
            {
                stream.Read<uint8_t>();
            }

        }
        for(GameObject* toRemove:objectRemaining){
            std::cout<<"Removed a GameObject "<<std::endl;
            this->replicatedObjects.erase(toRemove);
        }
    }
    else 
    {
        std::cout<<"Message du mauvais type"<<std::endl;
    }
    
}

GameObject* ReplicationManager::readOneGameObject(InputStream& stream, uint8_t& taille){
    NetworkID networkID;
    ReplicationClassID classID;
    
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