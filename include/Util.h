#include <iostream>

#include <iostream>
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

namespace util{
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