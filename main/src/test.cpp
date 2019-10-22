#include "packet_manager.hpp"
#include "linking_context.hpp"
#include "player.hpp"
#include <optional>
#include <iostream>

int main()
{
    
    Player a = Player();
    std::vector<GameObject*> v = std::vector<GameObject*>();
    LinkingContext::addToContext(&a);
    v.push_back(&a);
    InputStream stream = InputStream();
    PacketManager::createReplicationPacket(v,stream);
    std::cout<<"YAY"<<std::endl;
}