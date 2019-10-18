#include "game_object.hpp"
#include <string>
#include <map>

class ClassRegistry 
{
    private:
        std::map<ReplicationClassID,std::function<GameObject(void)>> classRegister;
        ~ClassRegistry();
    public:
        
        static ClassRegistry& getInstance(){
            static ClassRegistry instance;
            return instance;
        }
        
        GameObject Create(ReplicationClassID);
        void removeClassID(ReplicationClassID repCID);
        void addClassID(ReplicationClassID,std::function<GameObject(void)>);
};