#include <iostream>

#include <server.hpp>
#include <classRegistry.hpp>
#include <enemy.hpp>

#include <uvw.hpp>
#include <memory>

#include <chrono>
#include <thread>

int main() {
    std::cout<<"begin"<<std::endl;
    auto lambda = [] () { return Enemy(); };
    ClassRegistry::getInstance().addClassID(1,lambda);
    ClassRegistry::getInstance().Create(1);
    /*
    Server server = Server("127.0.0.1",4242);
	uint8_t test[1] = {0x34};

    while(true)
    {
        server.run();
        server.send(test,1);
    }
    */
}