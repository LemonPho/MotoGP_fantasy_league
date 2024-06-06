#ifndef MOTOGP_FANTASY_LEAGUE_MENU_H
#define MOTOGP_FANTASY_LEAGUE_MENU_H

#ifdef _WIN32
#define CLEAR "cls"
#elif defined(unix) || defined(__unix__) || defined(__APPLE__) || defined(__MACH__)
#define CLEAR "clear"
#else
#error "Operating system not supported, contact administrator"
#endif

#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <fstream>

#include "member-list.h"
#include "season-menu.h"
#include "member-menu.h"
#include "rider-menu.h"
#include "error-message.h"

using namespace std;

#define MEMBER_DATA "member-data.txt"
#define RIDER_DATA "rider-data.txt"
#define RACE_DATA "race-data.txt"
#define PROGRAM_DATA "program-data.txt"
#define CURRENT_STANDINGS "current-standings.txt"
#define CURRENT_STANDINGS_HTML "current-standings.html"

class Menu {
private:
    MemberList* memberList;
    RiderList* riderList;
    string seasonName;

    ErrorMessage memberErrorMessage;
    ErrorMessage riderErrorMessage;
public:
    Menu();

    void firstStart();
    void startProgram();
    void menu();
    void exit();
};

enum{
    SEASONS_MANAGER = 1,
    MEMBERS_MANAGER,
    RIDERS_MANAGER,
    EXIT_MENU
};

#endif //MOTOGP_FANTASY_LEAGUE_MENU_H
