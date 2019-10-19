#include "player.hpp"

int Player::Write(OutputStream& stream)
{

    //float to int compression
    int data = (int) (Player::position.pos_x * 1000);
    stream.Write(data);
    
    data = (int) (    Player::position.pos_y * 1000);
    stream.Write(data);

    data = (int) (Player::position.pos_z* 1000);
    stream.Write(data);

    if(Player::rotation.r_x > Player::rotation.r_y && Player::rotation.r_x > Player::rotation.r_z && Player::rotation.r_x > Player::rotation.r_w) // X
    {
        
    }
    else if(Player::rotation.r_y > Player::rotation.r_x && Player::rotation.r_y > Player::rotation.r_z && Player::rotation.r_y > Player::rotation.r_w) // Y
    {

    }
    else if(Player::rotation.r_z > Player::rotation.r_x && Player::rotation.r_z > Player::rotation.r_y && Player::rotation.r_z > Player::rotation.r_w) // Z
    {

    }
    else // W
    {

    }

    stream.Write(Player::nom);
    return 0;
}

int Player::Read(InputStream& stream)
{
    //int to float decompression
    /*
    Player::posX =  (float) stream.Read<int>() / 1000;
    Player::posY =  (float) stream.Read<int>() / 1000;
    Player::posZ =  (float) stream.Read<int>() / 1000;
    */


    stream.Write(Player::nom);

    return 0;
}