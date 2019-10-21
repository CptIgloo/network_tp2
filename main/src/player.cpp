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
	uint64_t posData = stream.Read<uint64_t>();
	uint64_t z = 0x00000000000FFFFF & posData;
	uint64_t y = 0x00000000000FFFFF & posData >> 20;
	uint64_t x = 0xFFFFF & posData >> 20;

    float fx = y -500000;
    float fy = y -500000;
    float fz = y -500000;

	position.pos_x = fx / 1000;
	position.pos_y = fy / 1000;
	position.pos_z = fz / 1000;

	uint32_t receivedQuat = stream.Read<uint32_t>();
	uint8_t caseToIgnore = 0x2 & receivedQuat;

	uint8_t offset = 2;
	uint32_t sumSquareRoot = 0;
	if (caseToIgnore != 0)
	{
		rotation.r_x = (static_cast<float>((0x3FF & receivedQuat >> offset) * 1047) / 1000) - 0.707;
		sumSquareRoot += rotation.r_x  * rotation.r_x ;
		offset += 10;
	}
	if (caseToIgnore != 1)
	{
		rotation.r_y = (static_cast<float>((0x3FF & receivedQuat >> offset) * 1047) / 1000) - 0.707;
		sumSquareRoot += rotation.r_y * rotation.r_y;
		offset += 10;
	}
	if (caseToIgnore != 2)
	{
		rotation.r_z = (static_cast<float>((0x3FF & receivedQuat >> offset) * 1047) / 1000) - 0.707;
		sumSquareRoot += rotation.r_z * rotation.r_z;
		offset += 10;
	}
	if (caseToIgnore != 3)
	{
		rotation.r_w = (static_cast<float>((0x3FF & receivedQuat >> offset) * 1047) / 1000) - 0.707;
		sumSquareRoot += rotation.r_w  * rotation.r_w ;
	}

	if (caseToIgnore == 0) {
		rotation.r_x = sqrtf(1.0f - sumSquareRoot);
	}
	if (caseToIgnore == 1) {
		rotation.r_y  = sqrtf(1.0f - sumSquareRoot);
	}
	if (caseToIgnore == 2) {
		rotation.r_z = sqrtf(1.0f - sumSquareRoot);
	}
	if (caseToIgnore == 3) {
		rotation.r_w = sqrtf(1.0f - sumSquareRoot);
	}

    name = stream.ReadStr();
    return 0;
}