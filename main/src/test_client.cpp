#include <uvw.hpp>
#include <iostream>

void conn(uvw::Loop &loop) {
    auto tcp = loop.resource<uvw::TCPHandle>();

    tcp->on<uvw::ErrorEvent>([](const uvw::ErrorEvent &e, uvw::TCPHandle &) { std::cout<<"Error "<<e.what()<<std::endl; });

    tcp->on<uvw::ConnectEvent>([](const uvw::ConnectEvent &, uvw::TCPHandle &tcp) {
        std::cout<<"Connected !"<<std::endl;
    });

    tcp->on<uvw::EndEvent>([](const uvw::EndEvent &, uvw::TCPHandle &tcp) { 
        
    });

    tcp->on<uvw::DataEvent>([](const uvw::DataEvent& evt, uvw::TCPHandle &){
        std::cout << "Received " << evt.data << std::endl;
    });

    tcp->connect(std::string{"127.0.0.1"}, 4242);

    tcp->read();
}

int main()
{   
    auto loop = uvw::Loop::getDefault();
    conn(*loop);

    while(true)
    {
        loop->run();
    }
}