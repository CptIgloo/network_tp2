#include "packet_manager.hpp"

std::string PacketManager::createReplicationPacket(std::vector<GameObject*> objects)
{
    std::string output = "";

    //PROTOCOL

    output += (char) 0xc0;
    output += (char) 0xde;

    //TYPE

    output += (char) PacketType::Sync;

    //Construction data 

    //N_ID (2) - C_ID (1) - SIZE (1) - DATA

    std::string data_builder = "";
    for(GameObject* object : objects)
    {
        std::optional<NetworkID> n_id_optional = LinkingContext::getIdOfObject(object);

        if(n_id_optional.has_value())
        {
            //Network id = 2 octets => AB
            NetworkID n_id = n_id_optional.value();
            //On récupère B
            char B = n_id & 0xff; 
            //Shift pour récupérer A
            char A = n_id >> 8;

            data_builder += A;
            data_builder += B;

            //TODO Mettre en prod
            /*
            // Class ID 1 octet
            ReplicationClassID r_id = object->classID;
            data_builder += (char) r_id
            */

            //Récupération data
            OutputStream objectData;
            object->Write(objectData);
            std::string formated_data = objectData.ReadStr();

            //Ajoute la taille de la data (En principe un octet suffit)
            data_builder += (char)(formated_data.size() & 0xFF); 
            data_builder += formated_data;
        }
        else
        {
            //Silently ignore
        }
    }
    
    //Data total size 2 octets
    uint16_t data_size = (data_builder.size() && 0xFFFF);
    //On récupère B
    char B = data_size & 0xff; 
    //Shift pour récupérer A
    char A = data_size >> 8;

    output += A;
    output += B;

    return output;
}

std::optional<std::vector<std::byte>> PacketManager::parsePacket(std::vector<std::byte>)
{
    return {};
}