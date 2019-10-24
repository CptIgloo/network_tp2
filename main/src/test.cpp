#include "linking_context.hpp"
#include "player.hpp"
#include <optional>
#include <iostream>

int main()
{
    OutputStream stream;
    uint8_t a = 0x41;
    stream.Write<uint8_t>(a);
    gsl::span<std::byte> b = stream.Data();
    std::string builder = "";
    for(std::byte byte : b)
    {
        builder += (char)byte;
    }
    uint8_t* test = (uint8_t*)builder.c_str();
    std::cout<<test<<std::endl;
}