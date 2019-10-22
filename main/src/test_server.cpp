#include <iostream>

#include <server.hpp>

#include <uvw.hpp>
#include <memory>

int main() {
    Server server = Server("127.0.0.1",4242);

    while(true)
    {
        char a[1] = {(char)0x41};
        server.run();
        server.send((uint8_t*)a,1);
    }
}