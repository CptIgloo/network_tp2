#include "game_object.hpp"
#include <string>
#include <map>
#include "enemy.hpp"
#include "player.hpp"

class ClassRegistry 
{
    private:
        std::map<ReplicationClassID,std::function<GameObject*(void)>> classRegister;
        ClassRegistry() = default;
        ~ClassRegistry();
    public:
        static ClassRegistry& getInstance(){
            static ClassRegistry instance;
            return instance;
        }

        template<class T>
        void Register(T classToAdd)
        {
            classRegister.insert(std::make_pair(classToAdd.ClassID(), classToAdd.CreateInstance));
        }

        GameObject* Create(ReplicationClassID repCID);
};