#include <iostream>

#include <server.hpp>
#include <replication_manager.hpp>
#include <classRegistry.hpp>
#include <enemy.hpp>
#include <client.hpp>

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
    //TODO
}

int main(int argc, char *argv[]) 
{
    ReplicationManager r;
    std::vector<std::byte> data={(std::byte)0x00,(std::byte)0x01,(std::byte)0x03,(std::byte)0x05,(std::byte)0x06};
    //data.push_back((std::byte)0x00);
    /*data[1]=1;
    data[2]=3;
    data[3]=5;
    data[4]=6;
    */
    InputStream in= InputStream(data);
    ClassRegistry::getInstance().standardInit();
    //in.Write(data);

    r.Replicate(in);
    /*
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

    //Already checked, type can only be server or client
    if(type == "server")
    {
            runAsServer();
    }
    else
    {
        runAsClient(ip,port);
    }
*/
    return EXIT_SUCCESS;
}