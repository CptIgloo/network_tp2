#include <iostream>

#include <server.hpp>
#include <client.hpp>

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

    std::cout<<"Executing "<<type<<" at ip "<<ip<<" with port "<<port<<std::endl;

    return EXIT_SUCCESS;
}