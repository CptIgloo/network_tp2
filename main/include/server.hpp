#include <vector>
#include <uvw.hpp>
#include <memory>
#include <game_object.hpp>

class Server
{
    private :
        std::vector<std::shared_ptr<uvw::TCPHandle>> clients;
        std::vector<GameObject*> world;
        std::shared_ptr<uvw::Loop> loop;
        std::string ip;
        int port;
    public :
        Server(std::string ip,int port);
        ~Server();
        
        void updateWorld();
        void run();
        void send(uint8_t* data,int size);
};