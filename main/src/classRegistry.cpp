#include "classRegistry.hpp"


ClassRegistry::~ClassRegistry(){
    this->classRegister.clear();
}

GameObject* ClassRegistry::Create(ReplicationClassID repCID)
{
    if(this->classRegister.find(repCID)!=this->classRegister.end()){
        return this->classRegister[repCID]();
    }
    //TODO Cleanup ? 
    return {};
}