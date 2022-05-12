cmake_minimum_required(VERSION 3.22)
project(MotoGP_fantasy_league)

set(CMAKE_CXX_STANDARD 14)

add_executable(MotoGP_fantasy_league
        src/main.cpp
        include/member.h
        src/member.cpp include/rider.h src/rider.cpp include/name.h src/name.cpp include/util.h include/member-node.h src/member-node.cpp include/member-list.h src/member-list.cpp include/menu.h src/menu.cpp)

target_include_directories(MotoGP_fantasy_league PRIVATE ./include)
