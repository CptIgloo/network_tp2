#include "player.hpp"

int Player::Write(OutputStream &stream)
{
    //float to int compression
    uint32_t posX = (uint32_t)((position.pos_x * 1000) + 500000);

    uint32_t PosY = (uint32_t)((position.pos_y * 1000) + 500000);

    uint32_t PosZ = (uint32_t)((position.pos_z * 1000) + 500000);

    uint64_t dataPos = posX << 20 + PosY << 20 + PosZ;
    stream.Write<uint64_t>(dataPos);

    if (rotation.r_x > rotation.r_y && rotation.r_x > rotation.r_z && rotation.r_x > rotation.r_w) // X
    {
        rotation.compression = 0;
    }
    else if (rotation.r_y > rotation.r_x && rotation.r_y > rotation.r_z && rotation.r_y > rotation.r_w) // Y
    {
        rotation.compression = 1;
    }
    else if (rotation.r_z > rotation.r_x && rotation.r_z > rotation.r_y && rotation.r_z > rotation.r_w) // Z
    {
        rotation.compression = 2;
    }
    else if (rotation.r_w > rotation.r_x && rotation.r_w > rotation.r_y && rotation.r_w > rotation.r_z)
    {
        rotation.compression = 3;
    }
    else
    {
        rotation.compression = 5;
    }

    uint32_t dataQuaternion = rotation.compression;

    uint8_t offset = 2;
    if (rotation.compression != 0)
    {
        dataQuaternion += (static_cast<uint32_t>((((rotation.r_x + 0.707) * 1000) / 1047) * 1024) << offset);
        offset += 10;
    }
    if (rotation.compression != 1)
    {
        dataQuaternion += (static_cast<uint32_t>((((rotation.r_y + 0.707) * 1000) / 1047) * 1024) << offset);
        offset += 10;
    }
    if (rotation.compression != 2)
    {
        dataQuaternion += (static_cast<uint32_t>((((rotation.r_z + 0.707) * 1000) / 1047) * 1024) << offset);
        offset += 10;
    }
    if (rotation.compression != 3)
    {
        dataQuaternion += (static_cast<uint32_t>((((rotation.r_w + 0.707) * 1000) / 1047) * 1024) << offset);
    }

    stream.Write<uint32_t>(dataQuaternion);

    stream.WriteStr(name);
    return 0;
}

int Player::Read(InputStream &stream)
{
    name = stream.ReadStr();
    return 0;
}