#include "game_object.hpp"
#include <string>
#include <map>

class ClassRegistry 
{
    private:
        std::map<ReplicationClassID,std::function<GameObject(void)>> classRegister;
        ClassRegistry() = default;
        ~ClassRegistry();
    public:
        static ClassRegistry& getInstance(){
            static ClassRegistry instance;
            return instance;
            
        }
        GameObject Create(ReplicationClassID repCID);
        void removeClassID(ReplicationClassID repCID);
        void addClassID(ReplicationClassID repCID,std::function<GameObject(void)> fun);
};