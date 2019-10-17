#include "linking_context.hpp"

using NetworkID = uint16_t;

NetworkID LinkingContext::currentID = 0;
std::map<NetworkID,GameObject*> LinkingContext::idToPointerMap = std::map<NetworkID,GameObject*>();
std::map<GameObject*,NetworkID> LinkingContext::pointerToIdMap = std::map<GameObject*,NetworkID>();

void LinkingContext::addToContextWithId(GameObject* toAdd,NetworkID idToAdd)
{
    currentID = idToAdd + 1;
    pointerToIdMap.insert(std::pair<GameObject*,NetworkID>(toAdd,idToAdd));
    idToPointerMap.insert(std::pair<NetworkID,GameObject*>(idToAdd,toAdd));
}

void LinkingContext::deleteFromContext(GameObject* toDelete)
{
    if(pointerToIdMap.find(toDelete) != pointerToIdMap.end())
    {
        NetworkID id = pointerToIdMap[toDelete];
        pointerToIdMap.erase(toDelete);
        idToPointerMap.erase(id);
    }
}

void LinkingContext::addToContext(GameObject* toAdd)
{
    pointerToIdMap.insert(std::pair<GameObject*,NetworkID>(toAdd,currentID));
    idToPointerMap.insert(std::pair<NetworkID,GameObject*>(currentID,toAdd));
    currentID++;
}

std::optional<NetworkID> LinkingContext::getIdOfObject(GameObject * search)
{
    if(pointerToIdMap.find(search) != pointerToIdMap.end())
    {
        return pointerToIdMap[search];
    }
    else
    {
        return {};
    }
    
}

std::optional<GameObject*> LinkingContext::getObjectOfId(NetworkID search)
{
    if(idToPointerMap.find(search) != idToPointerMap.end())
    {
        return idToPointerMap[search];
    }
    else
    {
        return {};
    }
}
