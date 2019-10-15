#include <vector>
#include <uvw.hpp>
#include <memory>

class Server
{
    private :
        std::vector<std::shared_ptr<uvw::TCPHandle>> clients;
        std::shared_ptr<uvw::Loop> loop;

        std::string ip;
        int port;

    public :
        Server(std::string ip,int port);
        ~Server();

        void Run();
        void Send(uint8_t* data,int size);
};