enum class PacketType : uint8_t
{
    Hello = 0x00,
    Sync = 0x01,
    Bye = 0x02,
    PacketType_Max
};

const 

struct Packet
{
    PacketType type;
    char* data;
};

class PacketManager
{

};