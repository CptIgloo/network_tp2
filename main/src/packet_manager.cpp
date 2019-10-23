#include "packet_manager.hpp"

void PacketManager::createReplicationPacket(std::vector<std::shared_ptr<GameObject>> objects,InputStream &stream)
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
    for(std::shared_ptr<GameObject> object : objects)
    {
        std::optional<NetworkID> n_id_optional = LinkingContext::getIdOfObject(object);

        if(n_id_optional.has_value())
        {
            data_builder.Write<NetworkID>(n_id_optional.value());
        
            // Class ID 1 octet
            ReplicationClassID r_id = object->ClassID();
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
    uint16_t data_size = (data_builder.Size() & 0xFFFF);

    stream.Write<uint16_t>(data_size);

    stream.Write(data_builder.Read(data_builder.Size()));
}

std::optional<OutputStream> PacketManager::parsePacketAndGetData(OutputStream stream)
{
    //Protocol

    uint16_t received_protocol = stream.Read<uint16_t>();

    if(received_protocol != PacketManager::protocol)
    {
        return {};
    }

    //Type 

    uint8_t received_type = stream.Read<uint8_t>();
    uint8_t expected_type = (uint8_t) PacketType::Sync;
    
    if(received_type !=  expected_type)
    {
        return {};
    }

    //Size
    int received_size = (int) stream.Read<uint16_t>();
    int expected_size = stream.RemainingSize();
    if( received_size != expected_size)
    {
        return {};
    }

    OutputStream output;
    output.Write(stream.Read(stream.RemainingSize()));

    return output;
}