#include <uvw.hpp>
#include <memory>

class Client
{
    private :
        std::shared_ptr<uvw::Loop> loop;
        std::string ip;
        int port;
    public :
        Client(std::string ip,int port);
        ~Client();

        void Run();
};
