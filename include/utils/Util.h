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
#include <sys/ioctl.h>
#include <unistd.h>
#define CLEAR "clear"
#endif

namespace util{
    inline const std::string PROGRAM_DATA = "program-data.txt";
    inline const std::string MEMBER_DATA = "-member-data.txt";
    inline const std::string RIDER_DATA = "-rider-data.txt";
    inline const std::string RACE_DATA = "-race-data.txt";
    inline std::filesystem::path APP_DIRECTORY;
    inline std::filesystem::path APP_DIRECTORY_DATA;
    inline std::filesystem::path APP_DIRECTORY_LOG;
    inline std::filesystem::path DOWNLOADS_DIRECTORY;

    std::string FillSpaces(std::string line, int spaces);
    void gotoxy(size_t x, size_t y);
    void UpdateArrowPosition(size_t line, size_t left, size_t right);
    void ClearText(size_t start, size_t end, size_t left, size_t right);
    void ClearBuffer();
    void EnterToContinue();
    int CheckIfSelected(const int selections[], int selectionsLength, int query);
    int CustomGetch();
    void GetWindowDimensions(int& columns, int& rows);
    void UpdateProgram();
}