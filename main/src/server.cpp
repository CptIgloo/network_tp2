#include "server.hpp"
#include <algorithm>
#include <iostream>
#include <thread>

Server::Server(std::string ip,int port)
{
    this->ip = ip;
    this->port = port;
    this->loop = uvw::Loop::getDefault();

    std::shared_ptr<uvw::TCPHandle> tcp = this->loop->resource<uvw::TCPHandle>();

    tcp->on<uvw::ListenEvent>([this](const uvw::ListenEvent &, uvw::TCPHandle &srv) {
        std::shared_ptr<uvw::TCPHandle> client = srv.loop().resource<uvw::TCPHandle>();
        client->on<uvw::CloseEvent>([ptr = srv.shared_from_this(),this](const uvw::CloseEvent &, uvw::TCPHandle &) { 
            ptr->close();
        });

        client->on<uvw::EndEvent>([this](const uvw::EndEvent &, uvw::TCPHandle &client) { 
            client.close();
        });

        client->on<uvw::ErrorEvent>([this](const uvw::ErrorEvent &e, uvw::TCPHandle &client){
            std::cout<<"Error : "<<e.what()<<std::endl;
            
            client.close();
            int i =0;
            for(std::vector<std::shared_ptr<uvw::TCPHandle>>::iterator it = clients.begin();it!=clients.end();++it)
            {   
                if(clients.at(i)->peer().ip == client.peer().ip && clients.at(i)->peer().port == client.peer().port)
                {
                    clients.erase(it);
                    break;
                }

                i++;
            }
        });

        client->on<uvw::WriteEvent>([](const uvw::WriteEvent &e, uvw::TCPHandle &client){
            std::cout<<"Ecriture ! "<<std::endl;
        });

        srv.accept(*client);
        
        std::cout<<"Accepted client at "<<client->peer().ip<<std::endl;
        clients.push_back(client);
    });

    tcp->bind(this->ip, this->port);
    tcp->listen();

    std::cout<<"Accepting clients"<<std::endl;
}

Server::~Server()
{
    this->clients.clear();
    this->loop->close();
}

void Server::run()
{   
    this->loop->run<uvw::Loop::Mode::NOWAIT>();
}

void Server::send(uint8_t* data,int size)
{
    for(std::shared_ptr<uvw::TCPHandle> client : clients)
    {   
        client->write((char*)data, size);
    }
}