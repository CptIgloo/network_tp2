#include "classRegistry.hpp"

GameObject ClassRegistry::Create(ReplicationClassID repCID){
    if(classRegister.find(repCID)!=classRegister.end()){
        return classRegister[repCID]();
    }
    assert(EXIT_FAILURE);
}