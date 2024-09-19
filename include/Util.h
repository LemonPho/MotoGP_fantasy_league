#pragma once

#include <iostream>
#include <filesystem>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

namespace util{
    extern const std::string PROGRAM_DATA;
    extern const std::string MEMBER_DATA;
    extern const std::string RIDER_DATA;
    extern const std::string RACE_DATA;
    extern std::filesystem::path APP_DIRECTORY;
    extern std::filesystem::path APP_DIRECTORY_DATA;
    extern std::filesystem::path APP_DIRECTORY_LOG;

    std::string FillSpaces(std::string line, int spaces);
    void gotoxy(int x, int y);
    void PrintMenu(std::string menuOptions[], int optionCount);
    void UpdateMenu(int option, int left, int right);
    void ClearSelection(int start, int end, int left, int right);
    void ClearBuffer();
    void EnterToContinue();
    int CheckIfSelected(const int selections[], int selectionsLength, int query);
    int CustomGetch();
    void UpdateProgram();
}