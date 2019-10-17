cmake_minimum_required(VERSION 3.10)

set(replication_sources src/main.cpp
                        src/game_object.cpp
                        src/player.cpp
                        src/enemy.cpp
                        src/streams.cpp
                        src/linking_context.cpp
                        src/server.cpp)

set(test_client_sources src/test_client.cpp
                        src/game_object.cpp
                        src/player.cpp
                        src/enemy.cpp
                        src/streams.cpp
                        src/linking_context.cpp
                        src/server.cpp)

include_directories(include)
set(replication_headers include/game_object.hpp
                        include/utils.hpp
                        include/player.hpp
                        include/enemy.hpp
                        include/streams.hpp
                        include/linking_context.hpp
                        include/server.hpp)

add_executable(tp2 ${replication_sources} ${replication_headers})
add_executable(test ${test_client_sources} ${replication_headers})
target_link_libraries(tp2 PUBLIC uvw_interface GSL)
target_link_libraries(test PUBLIC uvw_interface GSL)