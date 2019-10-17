#include <uvw.hpp>
#include <iostream>

void conn(uvw::Loop &loop) {
    auto tcp = loop.resource<uvw::TCPHandle>();

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

        //TODO Parser paquet !
        std::cout<<"Recu : "<<parser<<std::endl;
    });

    tcp->connect(std::string{"127.0.0.1"}, 4242);
}

int main()
{   
    std::cout<<"Connecting"<<std::endl;
    std::shared_ptr<uvw::Loop> loop = uvw::Loop::getDefault();
    conn(*loop);
    while(true)
    {
        loop->run<uvw::Loop::Mode::NOWAIT>();
    }
}