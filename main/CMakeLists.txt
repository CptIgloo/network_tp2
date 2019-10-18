cmake_minimum_required(VERSION 3.10)

set(replication_sources src/game_object.cpp
                        src/player.cpp
                        src/enemy.cpp
                        src/streams.cpp
                        src/linking_context.cpp
                        src/server.cpp
                        src/client.cpp)

set(main_sources        src/main.cpp
                        ${replication_sources})

set(test_server_sources src/test_server.cpp
                        ${replication_sources})

set(test_client_sources src/test_client.cpp
                        ${replication_sources})

set(test_sources        src/test.cpp
                        ${replication_sources})

include_directories(include)
set(replication_headers include/game_object.hpp
                        include/utils.hpp
                        include/player.hpp
                        include/enemy.hpp
                        include/streams.hpp
                        include/linking_context.hpp
                        include/server.hpp
                        include/client.hpp)

add_executable(tp2 ${main_sources} ${replication_headers})
add_executable(test_client ${test_client_sources} ${replication_headers})
add_executable(test_server ${test_server_sources} ${replication_headers})
add_executable(test ${test_sources} ${replication_headers})

target_link_libraries(tp2 PUBLIC uvw_interface GSL)
target_link_libraries(test_server PUBLIC uvw_interface GSL)
target_link_libraries(test_client PUBLIC uvw_interface GSL)
target_link_libraries(test PUBLIC uvw_interface GSL)