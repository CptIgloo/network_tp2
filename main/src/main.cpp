#include <iostream>

#include <server.hpp>

#include <uvw.hpp>
#include <memory>

#include <chrono>
#include <thread>

int main() {
    Server server = Server("127.0.0.1",4242);
	uint8_t test[1] = {0x34};

    while(true)
    {
        server.run();
        server.send(test,1);
    }
}