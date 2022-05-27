#ifndef MOTOGP_FANTASY_LEAGUE_RIDER_MENU_H
#define MOTOGP_FANTASY_LEAGUE_RIDER_MENU_H

#include <iostream>
#include "menu.h"

class RiderMenu {
private:
    RiderList* riderList;
    string seasonName;
    bool saveChanges;
public:
    RiderMenu(RiderList *riderList, string &seasonName);

    void menu();
    bool addRider();
    bool addRaceResults();
    bool deleteRider();
    void listRiders();

    void enterToContinue();
};

enum{
    ADD_RIDER = 1,
    ADD_RACE_RESULTS,
    DELETE_RIDER,
    LIST_RIDERS,
    DELETE_ALL_RIDERS,
    SAVE_CHANGES_RIDERS,
    EXIT_RIDER
};

#endif //MOTOGP_FANTASY_LEAGUE_RIDER_MENU_H
