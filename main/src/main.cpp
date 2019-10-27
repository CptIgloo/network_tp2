#include <iostream>

#include <server.hpp>
#include <replication_manager.hpp>
#include <classRegistry.hpp>
#include <linking_context.hpp>
#include <client.hpp>
#include <thread>
#include <future>
#include <numeric>
#include <chrono>

void runAsClient(std::string ip,int port)
{
    std::cout<<"Connecting to "<<ip<<"on port "<<port<<std::endl;
    Client client = Client(ip,port);
    while(client.continueRunning())
    {
        client.Run();
    }
}

void runAsServer()
{
    using namespace std::chrono_literals;
    Server server = Server("127.0.0.1",4242);

    while(true)
    {
        server.run();
        server.updateWorld();
        std::this_thread::sleep_for(1s);
    }
}

int main(int argc, char *argv[]) 
{
    if(argc != 4)
    {
        std::cout<<"Error : Incorrect number of arguments"<<std::endl;

        #ifdef _WIN32
        std::cout<<"Expected : tp2.exe TYPE IP PORT"<<std::endl;
        #else
        std::cout<<"Expected : /tp2.a TYPE IP PORT"<<std::endl;
        #endif
        
        return EXIT_FAILURE;
    }

    std::string type = argv[1];

    if(type != "server" && type != "client")
    {
        std::cout<<"Error : Incorrect type argument"<<std::endl;
        std::cout<<"Expected : server or client"<<std::endl;
        return EXIT_FAILURE;
    }

    std::string ip = argv[2];

    int port = std::stoi(argv[3]);

    ClassRegistry::getInstance().standardInit();

    //Already checked, type can only be server or client
    if(type == "server")
    {
        runAsServer();
    }
    else
    {
        runAsClient(ip,port);
    }

    return EXIT_SUCCESS;
}