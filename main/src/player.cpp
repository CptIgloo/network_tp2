#include "player.hpp"
#include <iostream>

void Player::Destroy()
{
	return;
}

int Player::Write(OutputStream &stream)
{

    uint64_t posX = (uint32_t)((position.pos_x * 1000) + 500000);

    uint64_t PosY = (uint32_t)((position.pos_y * 1000) + 500000);

    uint64_t PosZ = (uint32_t)((position.pos_z * 1000) + 500000);

    uint64_t dataPos = posX << 20 ;
    dataPos += PosY << 20 ;
    dataPos += PosZ;

    stream.Write<uint64_t>(dataPos);

    uint32_t compression;
    if (rotation.r_x > rotation.r_y && rotation.r_x > rotation.r_z && rotation.r_x > rotation.r_w) // X
    {
        compression = 0;
    }
    else if (rotation.r_y > rotation.r_x && rotation.r_y > rotation.r_z && rotation.r_y > rotation.r_w) // Y
    {
        compression = 1;
    }
    else if (rotation.r_z > rotation.r_x && rotation.r_z > rotation.r_y && rotation.r_z > rotation.r_w) // Z
    {
       compression = 2;
    }
    else if (rotation.r_w > rotation.r_x && rotation.r_w > rotation.r_y && rotation.r_w > rotation.r_z)
    {
        compression = 3;
    }
    else
    {
        compression = 5;
    }

    uint32_t dataQuaternion = compression;

    uint8_t offset = 2;
    if (compression != 0)
    {
        dataQuaternion += (static_cast<uint32_t>((((rotation.r_x + 0.707) * 1000) / 1047) * 1024) << offset);
        offset += 10;
    }
    if (compression != 1)
    {
        dataQuaternion += (static_cast<uint32_t>((((rotation.r_y + 0.707) * 1000) / 1047) * 1024) << offset);
        offset += 10;
    }
    if (compression != 2)
    {
        dataQuaternion += (static_cast<uint32_t>((((rotation.r_z + 0.707) * 1000) / 1047) * 1024) << offset);
        offset += 10;
    }
    if (compression != 3)
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
	uint64_t z = 0xFFFFF & posData;
	uint64_t y = 0xFFFFF & (posData >> 20);
	uint64_t x = 0xFFFFF & (posData >> 20);

    float fx = (y - 500000 ) / 1000;
    float fy = (y - 500000 ) / 1000;
    float fz = (y - 500000 ) / 1000;

    if(!(-500.000f <= fx && fx <= 500.000f))
    {
        std::cout << "Error : fx not between -500f,500f" << std::endl;
        return -1;
    }
    if(!(-500.000f <= fy && fy <= 500.000f))
    {
        std::cout << "Error : fy not between -500f,500f" << std::endl;
        return -1;
    }
    if(!(-500.000f <= fz && fz <= 500.000f))
    {
        std::cout << "Error : fz not between -500f,500f" << std::endl;
        return -1;
    }
	position.pos_x = fx / 1000;
	position.pos_y = fy / 1000;
	position.pos_z = fz / 1000;

	uint32_t dataQuat = stream.Read<uint32_t>();
	uint8_t ignoredVal = 0x2 & dataQuat;

	uint8_t offset = 2;
	uint32_t sumSquareRoot = 0;
	
    float rX = 0 , rY = 0 , rZ = 0 , rW = 0;
    if (ignoredVal != 0)
	{
        rX =  (static_cast<float>((0x3FF & dataQuat >> offset) * 1047) / 1000) - 0.707; 
		sumSquareRoot += rX * rX ;
		offset += 10;
        if(!(-1.0f <=rX &&  rX <= 1.0f))
        {
           std::cout << "Error : rX not between -1f,1f" << std::endl;
           return -1;
        }
	}
	if (ignoredVal != 1)
	{
		rY =  (static_cast<float>((0x3FF & dataQuat >> offset) * 1047) / 1000) - 0.707; 
		sumSquareRoot += rY * rY ;
		offset += 10;
        rotation.r_y = rY;
        if(!(-1.0f <=rY &&  rY <= 1.0f))
        {
           std::cout << "Error : rY not between -1f,1f" << std::endl;
           return -1;
        }
	}
	if (ignoredVal != 2)
	{
		rZ =  (static_cast<float>((0x3FF & dataQuat >> offset) * 1047) / 1000) - 0.707; 
		sumSquareRoot += rZ * rZ ;
		offset += 10;
        rotation.r_z = rZ;
        if(!(-1.0f <=rZ &&  rZ <= 1.0f))
        {
           std::cout << "Error : rZ not between -1f,1f" << std::endl;
           return -1;
        }
	}
	if (ignoredVal != 3)
	{
		rW =  (static_cast<float>((0x3FF & dataQuat >> offset) * 1047) / 1000) - 0.707; 
		sumSquareRoot += rW * rW ;
        rotation.r_w= rW;
        if(!(-1.0f <=rW &&  rW <= 1.0f))
        {
           std::cout << "Error : rW not between -1f,1f" << std::endl;
           return -1;
        }
	}

    if(ignoredVal != 0)
    {
        rotation.r_x = rX;
    }
    if(ignoredVal != 1)
    {
        rotation.r_y = rY;
    }
    if(ignoredVal != 2)
    {
        rotation.r_z = rZ;
    }
    if(ignoredVal != 3)
    {
        rotation.r_w = rW;
    }

	if (ignoredVal == 0) {
		rotation.r_x = sqrtf(1.0f - sumSquareRoot);
	}
	if (ignoredVal == 1) {
		rotation.r_y  = sqrtf(1.0f - sumSquareRoot);
	}
	if (ignoredVal == 2) {
		rotation.r_z = sqrtf(1.0f - sumSquareRoot);
	}
	if (ignoredVal == 3) {
		rotation.r_w = sqrtf(1.0f - sumSquareRoot);
	}

    name = stream.ReadStr();
    return 0;
}