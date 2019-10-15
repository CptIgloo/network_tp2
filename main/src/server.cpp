#include "server.hpp"

Server::Server(std::string ip,int port)
{
    this->ip = ip;
    this->port = port;
    this->loop = uvw::Loop::getDefault();
}

void Server::Run()
{
     std::shared_ptr<uvw::TCPHandle> tcp = this->loop->resource<uvw::TCPHandle>();

    tcp->once<uvw::ListenEvent>([this](const uvw::ListenEvent &, uvw::TCPHandle &srv) {
        std::shared_ptr<uvw::TCPHandle> client = srv.loop().resource<uvw::TCPHandle>();
        client->on<uvw::CloseEvent>([ptr = srv.shared_from_this()](const uvw::CloseEvent &, uvw::TCPHandle &) { ptr->close(); });
        client->on<uvw::EndEvent>([this](const uvw::EndEvent &, uvw::TCPHandle &client) { 
            client.close();
            //clients.erase(std::remove_if(clients.begin(),clients.end(),&client));

        });
        srv.accept(*client);
        client->read();
        std::vector<int> test = {1,2,3,4};
        clients.push_back(client);
    });

    tcp->bind("127.0.0.1", 4242);
    tcp->listen();
}