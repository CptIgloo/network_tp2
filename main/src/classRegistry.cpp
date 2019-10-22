#include "classRegistry.hpp"


ClassRegistry::~ClassRegistry(){
    this->classRegister.clear();
}


void ClassRegistry::removeClassID(ReplicationClassID repCID){
    if(this->classRegister.find(repCID)!=this->classRegister.end()){
        this->classRegister.erase(repCID);
    }
    //TODO Optionnal
    assert(EXIT_FAILURE);
}

GameObject* ClassRegistry::Create(ReplicationClassID repCID)
{
    if(this->classRegister.find(repCID)!=this->classRegister.end()){
        return this->classRegister[repCID]();
    }
    //TODO Cleanup ? 
    return {};
}
 void ClassRegistry::standardInit(){
    ClassRegistry::getInstance().Register<Enemy>(Enemy());
    ClassRegistry::getInstance().Register<Player>(Player());
 }