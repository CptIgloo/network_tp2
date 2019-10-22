#include "packet_manager.hpp"
#include "linking_context.hpp"
#include "player.hpp"
#include <optional>
#include <iostream>

int main()
{
    std::vector<GameObject*> v = std::vector<GameObject*>();
    Player a = Player();
    Player b = Player();
    Player c = Player();
    LinkingContext::addToContext(&a);
    LinkingContext::addToContext(&b);
    LinkingContext::addToContext(&c);
    v.push_back(&a);
    v.push_back(&b);
    v.push_back(&c);
    InputStream stream = InputStream();
    PacketManager::createReplicationPacket(v,stream);
    OutputStream stream_out;
    stream_out.Write(stream.Read(stream.Size()));
    PacketManager::parsePacket(stream_out);
    std::cout<<"YAY"<<std::endl;
}