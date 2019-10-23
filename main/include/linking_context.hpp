#ifndef LINKING_CONTEXT_HPP
#define LINKING_CONTEXT_HPP
#include <optional>
#include "game_object.hpp"
#include <map>

using NetworkID = uint16_t;

class LinkingContext
{
    private :
        static std::map<NetworkID,std::shared_ptr<GameObject>> idToPointerMap;
        static std::map<std::shared_ptr<GameObject>,NetworkID> pointerToIdMap;

        /*
        On va juste augmenter l'id à la main un par un
        Dans notre cas c'est suffisant puisque seul le serveur va maniupler des objets qui n'ont pas d'id
        */
        static NetworkID currentID;

    public :
        static void addToContextWithId(std::shared_ptr<GameObject> toAdd,NetworkID idToAdd);
        static void deleteFromContext(std::shared_ptr<GameObject> toDelete);
        static void addToContext(std::shared_ptr<GameObject> toAdd);
        static int getSizeOfContext();
        static std::optional<NetworkID> getIdOfObject(std::shared_ptr<GameObject> search);
        static std::optional<std::shared_ptr<GameObject>> getObjectOfId(NetworkID search);
        static void clearContext();
};
#endif