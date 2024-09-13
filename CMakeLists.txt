cmake_minimum_required(VERSION 3.30)
project(MotoGP_Fantasy_League_Modern)

set(CMAKE_CXX_STANDARD 17)

add_executable(MotoGP_Fantasy_League src/main.cpp
        include/Logger.h
        include/Menu.h
        src/Logger.cpp
        src/Menu.cpp
        include/SeasonMenu.h
        src/SeasonMenu.cpp
        include/Core.h
        src/Core.cpp)

target_include_directories(MotoGP_Fantasy_League PRIVATE ${CMAKE_SOURCE_DIR}/include)
