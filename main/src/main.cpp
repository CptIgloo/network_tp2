#include <iostream>

#include <server.hpp>

#include <uvw.hpp>
#include <memory>

/*
void listen(uvw::Loop &loop) {
    std::shared_ptr<uvw::TCPHandle> tcp = loop.resource<uvw::TCPHandle>();

    tcp->once<uvw::ListenEvent>([](const uvw::ListenEvent &, uvw::TCPHandle &srv) {
        std::shared_ptr<uvw::TCPHandle> client = srv.loop().resource<uvw::TCPHandle>();

        client->on<uvw::CloseEvent>([ptr = srv.shared_from_this()](const uvw::CloseEvent &, uvw::TCPHandle &) { ptr->close(); });
        client->on<uvw::EndEvent>([](const uvw::EndEvent &, uvw::TCPHandle &client) { client.close(); });
        srv.accept(*client);
        client->read();
    });

    tcp->bind("127.0.0.1", 4242);
    tcp->listen();
}*/

int main() {
    Server server = Server("127.0.0.1",4242);
    server.run();
    std::cout<<"test"<<std::endl;
	uint8_t test[1] = {(uint8_t)48};
    while(true)
    {
        server.run();
        server.send(test,1);
    }
}