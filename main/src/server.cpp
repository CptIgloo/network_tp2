#include "server.hpp"
#include <algorithm>
#include <iostream>
#include <thread>
#include "player.hpp"
#include "enemy.hpp"
#include <random>
#include "replication_manager.hpp"

Server::Server(std::string ip,int port)
{
    this->ip = ip;
    this->port = port;
    this->loop = uvw::Loop::getDefault();

    Enemy* enemy_1 = (Enemy*) Enemy::CreateInstance();

    enemy_1->setPosition(0,10,25);
    enemy_1->setRotation(1,0,0,0);
    enemy_1->setType("Uno");

    Enemy* enemy_2 = (Enemy*) Enemy::CreateInstance();

    enemy_2->setPosition(-10,5,-40);
    enemy_2->setRotation(0,0,1,0);
    enemy_2->setType("Dos");

    Player* player = (Player*) Player::CreateInstance();

    player->setPosition(0,0,0);
    player->setRotation(0,0,1,0);
    player->setName("Jack");

    this->world.push_back(enemy_1);
    this->world.push_back(enemy_2);
    this->world.push_back(player);

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

    for(GameObject* object : world)
    {
        delete(object);
    }
}

void Server::run()
{   
    this->loop->run<uvw::Loop::Mode::NOWAIT>();
}

void Server::updateWorld()
{
    OutputStream output_stream;

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distr(-500,500); // define the range

    for(GameObject* object : world)
    {
        object->setPosition((int) distr(eng),(int) distr(eng),(int) distr(eng));
    }

    ReplicationManager::getInstance().Replicate(output_stream,world);
    gsl::span<std::byte> data_span = output_stream.Data();
    std::string pointer_builder = "";
    for(std::byte byte : data_span)
    {
        pointer_builder += (char)byte;
    }
    uint8_t* data_pointer = (uint8_t*)pointer_builder.c_str();

    this->send(data_pointer,pointer_builder.length());
}

void Server::send(uint8_t* data,int size)
{
    for(std::shared_ptr<uvw::TCPHandle> client : clients)
    {   
        client->write((char*)data, size);
    }
}

