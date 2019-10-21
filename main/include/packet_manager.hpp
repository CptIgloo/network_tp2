#include "linking_context.hpp"
#include "game_object.hpp"
#include <vector>
#include <optional>

enum class PacketType : uint8_t
{
    Hello = 0x00,
    Sync = 0x01,
    Bye = 0x02,
    PacketType_Max
};

struct Packet
{
    char protocol[2] = {(char)0xc0,(char)0xde};
    PacketType type;
    NetworkID network_id;  
    char* data;
    int data_size;
};

class PacketManager
{
    public :
        static std::string createReplicationPacket(std::vector<GameObject*> objects);
        static std::optional<std::vector<std::byte>> parsePacket(std::vector<std::byte>);
};