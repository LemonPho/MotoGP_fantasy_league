#ifndef MOTOGP_FANTASY_LEAGUE_RACE_RESULTS_MENU_H
#define MOTOGP_FANTASY_LEAGUE_RACE_RESULTS_MENU_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include "rider-list.h"
#include "member-list.h"
#include "race-result.h"
#include "race-result-list.h"
#include "menu.h"

using namespace std;

class RaceResultsMenu{
private:
    RaceResultList raceResultList;
    RiderList* riderList;
    MemberList* memberList;

    string seasonName;
    ErrorMessage errorMessage;
public:
    RaceResultsMenu(RiderList* riderList, MemberList* memberList, string seasonName);
    ~RaceResultsMenu();

    void menu();
    bool addRaceResultAutomatic(bool link);
    bool addRaceResultManual(bool isSprint);
    void showRaceResultsSmall();
    void showRaceResults();
    bool deleteRaceResult();
};

enum{
    AUTOMATIC_ADD_RESULT = 1,
    AUTOMATIC_ADD_RESULT_LINK,
    MANUAL_ADD_RACE_RESULT,
    MANUAL_ADD_SPRINT_RESULT,
    VIEW_RACE_RESULTS,
    DELETE_RACE_RESULT,
    EXIT_RACE_RESULT_MENU,
};

#endif //MOTOGP_FANTASY_LEAGUE_RACE_RESULTS_MENU_H
