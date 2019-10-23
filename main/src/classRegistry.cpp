#include "classRegistry.hpp"


ClassRegistry::~ClassRegistry(){
    this->classRegister.clear();
}

std::optional<std::shared_ptr<GameObject>> ClassRegistry::Create(ReplicationClassID repCID)
{
    if(this->classRegister.find(repCID)!=this->classRegister.end()){
        return this->classRegister[repCID]();
    }
    return {};
}