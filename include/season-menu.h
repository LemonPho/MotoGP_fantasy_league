#ifndef MOTOGP_FANTASY_LEAGUE_SEASON_MENU_H
#define MOTOGP_FANTASY_LEAGUE_SEASON_MENU_H

#include <iostream>
#include "menu.h"

using namespace std;

class SeasonMenu {
private:
    MemberList* memberList;
    string seasonName;
public:
    SeasonMenu(MemberList* memberList, string &seasonName);

    void menu();

    void createSeason();
    void changeSeason();
    void changeDefaultSeason();


    void enterToContinue();
};

enum{
    CREATE_SEASON = 1,
    SELECT_SEASON,
    CHANGE_DEFAULT_SEASON,
    EXIT_SEASON
};

#endif //MOTOGP_FANTASY_LEAGUE_SEASON_MENU_H
