#include "client.hpp"
#include <iostream>
#include "streams.hpp"
#include "replication_manager.hpp"

Client::Client(std::string ip,int port)
{
    this->ip = ip;
    this->port = port;

    this->loop = uvw::Loop::getDefault();

    auto tcp =  this->loop->resource<uvw::TCPHandle>();

    tcp->on<uvw::CloseEvent>([this](const uvw::CloseEvent &e,uvw::TCPHandle &tcp){
        this->Stop();
    });

    tcp->on<uvw::ErrorEvent>([](const uvw::ErrorEvent &e, uvw::TCPHandle &tcp) { 
        std::cout<<"Error "<<e.what()<<std::endl; 
        tcp.close();
    });

    tcp->on<uvw::ConnectEvent>([](const uvw::ConnectEvent &, uvw::TCPHandle &tcp) {
        std::cout<<"Connected !"<<std::endl;
        tcp.read();
    });

    tcp->on<uvw::EndEvent>([](const uvw::EndEvent &, uvw::TCPHandle &tcp) { 
        
    });

    tcp->on<uvw::DataEvent>([](const uvw::DataEvent& evt, uvw::TCPHandle &tcp)
    {
        OutputStream out = OutputStream();

        for(int i = 0;i<(int)evt.length;i++)
        {
            out.Write<char>(evt.data[i]);
        }
        
        ReplicationManager::Replicate(out);
    });

    tcp->connect(std::string{"127.0.0.1"}, 4242);
}

Client::~Client()
{
    this->loop->close();
}

void Client::Stop()
{
    this->continueToRun = false;
}

bool Client::continueRunning()
{
    return this->continueToRun;
}

void Client::Run()
{
    //TODO Est ce que y'as pas mieux ?
    loop->run<uvw::Loop::Mode::NOWAIT>();
}