#include "linking_context.hpp"

NetworkID LinkingContext::currentID = 0;
std::map<NetworkID,std::shared_ptr<GameObject>> LinkingContext::idToPointerMap = std::map<NetworkID,std::shared_ptr<GameObject>>();
std::map<std::shared_ptr<GameObject>,NetworkID> LinkingContext::pointerToIdMap = std::map<std::shared_ptr<GameObject>,NetworkID>();

void LinkingContext::addToContextWithId(std::shared_ptr<GameObject> toAdd,NetworkID idToAdd)
{
    currentID = idToAdd + 1;
    pointerToIdMap.insert(std::pair<std::shared_ptr<GameObject>,NetworkID>(toAdd,idToAdd));
    idToPointerMap.insert(std::pair<NetworkID,std::shared_ptr<GameObject>>(idToAdd,toAdd));
}

void LinkingContext::deleteFromContext(std::shared_ptr<GameObject> toDelete)
{
    if(pointerToIdMap.find(toDelete) != pointerToIdMap.end())
    {
        NetworkID id = pointerToIdMap[toDelete];
        pointerToIdMap.erase(toDelete);
        idToPointerMap.erase(id);
    }
}

void LinkingContext::addToContext(std::shared_ptr<GameObject> toAdd)
{
    pointerToIdMap.insert(std::pair<std::shared_ptr<GameObject>,NetworkID>(toAdd,currentID));
    idToPointerMap.insert(std::pair<NetworkID,std::shared_ptr<GameObject>>(currentID,toAdd));
    currentID++;
}

std::optional<NetworkID> LinkingContext::getIdOfObject(std::shared_ptr<GameObject> search)
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

std::optional<std::shared_ptr<GameObject>> LinkingContext::getObjectOfId(NetworkID search)
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

int LinkingContext::getSizeOfContext()
{
    return idToPointerMap.size();
}

void LinkingContext::clearContext()
{
    pointerToIdMap.clear();
    idToPointerMap.clear();
}