#ifndef MOTOGP_FANTASY_LEAGUE_RIDER_MENU_H
#define MOTOGP_FANTASY_LEAGUE_RIDER_MENU_H

#include <iostream>
#include "menu.h"
#include "member-menu.h"

class RiderMenu {
private:
    MemberList* memberList;
    RiderList* riderList;
    string seasonName;
    bool saveChanges;
public:
    RiderMenu(MemberList* memberList, RiderList *riderList, string &seasonName);

    void menu();
    bool addRider();
    bool addRaceResults();
    bool addSprintRaceResults();
    bool deleteRider();

    void updateMembersRiders();

    void enterToContinue();
};

enum{
    ADD_RIDER = 1,
    ADD_RACE_RESULTS,
    ADD_SPRINT_RACE_RESULTS,
    DELETE_RIDER,
    LIST_RIDERS,
    DELETE_ALL_RIDERS,
    SAVE_CHANGES_RIDERS,
    EXIT_RIDER
};

#endif //MOTOGP_FANTASY_LEAGUE_RIDER_MENU_H
