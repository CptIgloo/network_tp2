#include <iostream>

#include <server.hpp>

#include <uvw.hpp>
#include <memory>

int main() {
    Server server = Server("127.0.0.1",4242);

    while(true)
    {
        server.run();
    }
}