#ifndef LINKING_CONTEXT_HPP
#define LINKING_CONTEXT_HPP
#include <optional>
#include "game_object.hpp"
#include <map>

using NetworkID = uint16_t;

class LinkingContext
{
    private :
        static std::map<NetworkID,GameObject*> idToPointerMap;
        static std::map<GameObject*,NetworkID> pointerToIdMap;

        /*
        On va juste augmenter l'id à la main un par un
        Dans notre cas c'est suffisant puisque seul le serveur va maniupler des objets qui n'ont pas d'id
        */
        static NetworkID currentID;

    public :
        static void addToContextWithId(GameObject* toAdd,NetworkID idToAdd);
        static void deleteFromContext(GameObject* toDelete);
        static void addToContext(GameObject* toAdd);
        static int getSizeOfContext();
        static std::optional<NetworkID> getIdOfObject(GameObject * search);
        static std::optional<GameObject*> getObjectOfId(NetworkID search);
        static void clearContext();
};
#endif