#include "classRegistry.hpp"

ClassRegistry::ClassRegistry(){
}

ClassRegistry::~ClassRegistry(){
    this->classRegister.clear();
}

void ClassRegistry::addClassID(ReplicationClassID repCID,std::function<GameObject(void)> fun){
    this->classRegister.insert_or_assign(repCID,fun);
}

void ClassRegistry::removeClassID(ReplicationClassID repCID){
    if(this->classRegister.find(repCID)!=this->classRegister.end()){
        this->classRegister.erase(repCID);
    }
    assert(EXIT_FAILURE);
}

GameObject ClassRegistry::Create(ReplicationClassID repCID){
    if(this->classRegister.find(repCID)!=this->classRegister.end()){
        return this->classRegister[repCID]();
    }
    assert(EXIT_FAILURE);
}