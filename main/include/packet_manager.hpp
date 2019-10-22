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

class PacketManager
{
    public :
        static const uint16_t protocol = ((uint8_t)0xc0 << 8) | ((uint8_t)0xde);
        static void createReplicationPacket(std::vector<GameObject*> objects,InputStream &stream);
        static std::optional<OutputStream> parsePacket(OutputStream stream);
};