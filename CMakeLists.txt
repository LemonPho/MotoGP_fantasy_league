cmake_minimum_required(VERSION 3.22)
project(MotoGP_fantasy_league)

set(CMAKE_CXX_STANDARD 14)

add_executable(MotoGP_fantasy_league
        src/main.cpp
        include/member.h
        src/member.cpp
        include/rider.h
        src/rider.cpp
        include/util.h
        include/member-node.h
        src/member-node.cpp
        include/member-list.h
        src/member-list.cpp
        include/menu.h
        src/menu.cpp
        src/util.cpp
        include/race-result-scraper.h
        src/race-result-scraper.cpp
        include/rider-node.h
        include/rider-list.h
        src/rider-node.cpp
        src/rider-list.cpp
        include/season-menu.h
        include/member-menu.h
        include/rider-menu.h
        src/season-menu.cpp
        src/member-menu.cpp
        src/rider-menu.cpp
        src/rider-manager.cpp
        src/error-message.cpp
        src/race-result.cpp
        src/race-results-menu.cpp
        src/race-result-list.cpp)

target_link_libraries(MotoGP_fantasy_league -static)
target_include_directories(MotoGP_fantasy_league PRIVATE ./include)

set(LibXml2_INCLUDE_DIR "C:/msys64/mingw64/include/libxml2")
set(LibXml2_LIBRARIES "C:/msys64/mingw64/lib/libxml2.dll.a")
set(CURL_INCLUDE_DIR "C:/msys64/mingw64/include/curl")
set(CURL_LIBRARIES "C:/msys64/mingw64/lib/libcurl.dll.a")

include_directories(${CURL_INCLUDE_DIR})
include_directories(${LibXml2_INCLUDE_DIR})
link_directories("C:/msys64/mingw64/lib")

target_link_libraries(MotoGP_fantasy_league ${CURL_LIBRARIES})
target_link_libraries(MotoGP_fantasy_league ${LibXml2_LIBRARIES})