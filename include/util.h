#ifndef MOTOGP_FANTASY_LEAGUE_UTIL_H
#define MOTOGP_FANTASY_LEAGUE_UTIL_H

#include <iostream>
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

using namespace std;

string fillSpaces(string line, int spaces);
void gotoxy(int x, int y);
void printMenu(string menuOptions[], int optionCount);
void updateMenu(int option, int left, int right);
void clearSelection(int start, int end, int left, int right);
void clearBuffer();
void enterToContinue();
int checkIfSelected(const int selections[], int selectionsLength, int query);
int custom_getch();

#endif //MOTOGP_FANTASY_LEAGUE_UTIL_H
