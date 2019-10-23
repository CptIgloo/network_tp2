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
        static const uint16_t protocol;
        static void createReplicationPacket(std::vector<std::shared_ptr<GameObject>> objects,InputStream &stream);
        static std::optional<OutputStream> parsePacketAndGetData(OutputStream stream);
};