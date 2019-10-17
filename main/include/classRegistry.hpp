#include "game_object.hpp"
#include <string>
#include <map>

class ClassRegistry 
{
    private:
        static ClassRegistry *s_instance; 
        std::map<ReplicationClassID,std::function<GameObject(void)>> classRegister;
    public:
        static ClassRegistry* instance(){
            if (!s_instance)
                s_instance = new ClassRegistry;
            return s_instance;
        }
        ~ClassRegistry();
        GameObject Create(ReplicationClassID);
        void removeClassID(ReplicationClassID repCID);
        void addClassID(ReplicationClassID,std::function<GameObject(void)>);
};