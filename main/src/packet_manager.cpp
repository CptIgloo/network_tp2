#include "packet_manager.hpp"

void PacketManager::createReplicationPacket(std::vector<GameObject*> objects,InputStream &stream)
{
    stream.Flush();

    //Protocol

    stream.Write<const uint16_t>(PacketManager::protocol);

    //TYPE
    uint8_t type = (uint8_t)PacketType::Sync;
    stream.Write<uint8_t>(type);

    //Construction data 

    //N_ID (2) - C_ID (1) - SIZE (1) - DATA

    OutputStream data_builder;
    for(GameObject* object : objects)
    {
        std::optional<NetworkID> n_id_optional = LinkingContext::getIdOfObject(object);

        if(n_id_optional.has_value())
        {
            //Network id = 2 octets => AB
            NetworkID n_id = n_id_optional.value();
            //On récupère B
            uint8_t B = (uint8_t) (n_id & 0xff); 
            //Shift pour récupérer A
            uint8_t A = (uint8_t) (n_id >> 8);

            data_builder.Write<uint8_t>(A);
            data_builder.Write<uint8_t>(B);
        
            // Class ID 1 octet
            ReplicationClassID r_id = object->classID;
            data_builder.Write<ReplicationClassID>(r_id);
            
            //Récupération data
            OutputStream objectData;
            object->Write(objectData);
            gsl::span<std::byte> formated_data = objectData.Read(objectData.Size());
            //Ajoute la taille de la data (En principe un octet suffit)
            uint8_t data_size = (uint8_t)(formated_data.size() & 0xFF);
            data_builder.Write<uint8_t>(data_size); 
            data_builder.Write(formated_data);
        }
        else
        {
            //Silently ignore
        }
    }
    
    //Data total size 2 octets
    uint16_t data_size = (data_builder.Size() && 0xFFFF);
    //On récupère B
    uint8_t B = (uint8_t) (data_size & 0xff); 
    //Shift pour récupérer A
    uint8_t A = (uint8_t) (data_size >> 8);
    
    stream.Write<uint8_t>(A);
    stream.Write<uint8_t>(B);

    stream.Write(data_builder.Read(data_builder.Size()));
}

std::optional<OutputStream> PacketManager::parsePacket(OutputStream stream)
{
    return {};
}