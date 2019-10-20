#include <uvw.hpp>
#include <iostream>
#include "client.hpp"

int main()
{   
    std::cout<<"Connecting"<<std::endl;
    Client client = Client("127.0.0.1",4242);
    while(client.continueRunning())
    {
        client.Run();
    }
}