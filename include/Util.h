#pragma once

#include <iostream>
#include <filesystem>
#include <vector>

//certain libraries needed for different operating systems
#ifdef _WIN32
#include <conio.h>
#include <shlobj.h>
#include <windows.h>
#define CLEAR "cls"
#else
#include <termios.h>
#include <unistd.h>
#define CLEAR "clear"
#endif

namespace util{
    extern const std::string PROGRAM_DATA;
    extern const std::string MEMBER_DATA;
    extern const std::string RIDER_DATA;
    extern const std::string RACE_DATA;
    extern std::filesystem::path APP_DIRECTORY;
    extern std::filesystem::path APP_DIRECTORY_DATA;
    extern std::filesystem::path APP_DIRECTORY_LOG;
    extern std::filesystem::path DOWNLOADS_DIRECTORY;

    std::string FillSpaces(std::string line, int spaces);
    void gotoxy(size_t x, size_t y);
    void PrintMenu(std::vector<std::string> menuOptions);
    void UpdateArrowPosition(size_t line, size_t left, size_t right);
    void ClearText(size_t start, size_t end, size_t left, size_t right);
    void ClearBuffer();
    void EnterToContinue();
    int CheckIfSelected(const int selections[], int selectionsLength, int query);
    int CustomGetch();
    void UpdateProgram();
}