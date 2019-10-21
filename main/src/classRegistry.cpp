#include "classRegistry.hpp"


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
    //TODO Optionnal
    assert(EXIT_FAILURE);
}

GameObject ClassRegistry::Create(ReplicationClassID repCID){
    if(this->classRegister.find(repCID)!=this->classRegister.end()){
        return this->classRegister[repCID]();
    }
    assert(EXIT_FAILURE);
}
 void ClassRegistry::standardInit(){
    auto lambda = [] () { return Enemy(); };
    ClassRegistry::getInstance().addClassID(Enemy::classID,lambda);
    auto lambda2=[] () { return Player(); };
    ClassRegistry::getInstance().addClassID(Player::classID,lambda2);
 }