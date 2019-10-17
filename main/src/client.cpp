#include "client.hpp"
#include <iostream>

Client::Client(std::string ip,int port)
{
    this->ip = ip;
    this->port = port;

    this->loop = uvw::Loop::getDefault();

    auto tcp =  this->loop->resource<uvw::TCPHandle>();

    tcp->on<uvw::ErrorEvent>([](const uvw::ErrorEvent &e, uvw::TCPHandle &) { std::cout<<"Error "<<e.what()<<std::endl; });

    tcp->on<uvw::ConnectEvent>([](const uvw::ConnectEvent &, uvw::TCPHandle &tcp) {
        std::cout<<"Connected !"<<std::endl;
        tcp.read();
    });

    tcp->on<uvw::EndEvent>([](const uvw::EndEvent &, uvw::TCPHandle &tcp) { 
        
    });

    tcp->on<uvw::DataEvent>([](const uvw::DataEvent& evt, uvw::TCPHandle &)
    {
        std::string parser;

        for(int i = 0;i<(int)evt.length;i++)
        {
            parser += evt.data[i];
        }

        uint8_t* received = (uint8_t*) parser.c_str();
        
        //TODO Parser paquet !
        std::cout<<"Recu : "<<parser<<std::endl;
    });

    tcp->connect(std::string{"127.0.0.1"}, 4242);
}

Client::~Client()
{
    this->loop->close();
}

void Client::Run()
{
    //TODO Est ce que y'as pas mieux ?
    loop->run<uvw::Loop::Mode::NOWAIT>();
}