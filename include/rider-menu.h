#ifndef MOTOGP_FANTASY_LEAGUE_RIDER_MENU_H
#define MOTOGP_FANTASY_LEAGUE_RIDER_MENU_H

#include <iostream>

#include "race-results-menu.h"
#include "menu.h"
#include "member-menu.h"
#include "race-result-scraper.h"
#include "error-message.h"

class RiderMenu {
private:
    MemberList* memberList;
    RiderList* riderList;
    string seasonName;
    bool saveChanges;

    ErrorMessage *errorMessage;
public:
    RiderMenu(MemberList* memberList, RiderList *riderList, string &seasonName, ErrorMessage *errorMessage);

    void menu();
    bool addRider();
    bool deleteRider();
};

enum{
    RACE_RESULTS_MENU = 1,
    ADD_RIDER,
    DELETE_RIDER,
    LIST_RIDERS,
    DELETE_ALL_RIDERS,
    SAVE_CHANGES_RIDERS,
    EXIT_RIDER
};

#endif //MOTOGP_FANTASY_LEAGUE_RIDER_MENU_H
