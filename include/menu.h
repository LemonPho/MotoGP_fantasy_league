#ifndef MOTOGP_FANTASY_LEAGUE_MENU_H
#define MOTOGP_FANTASY_LEAGUE_MENU_H

#include <iostream>
#include <sys/stat.h>
#include "member-list.h"


using namespace std;

#define FILENAME "member-data.txt"

class Menu {
private:
    MemberList* memberList;
    string currentDirectory;
public:
    Menu();

    void firstStart();
    void menu();
    void enterToContinue();
};

#endif //MOTOGP_FANTASY_LEAGUE_MENU_H
