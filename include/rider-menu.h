#ifndef MOTOGP_FANTASY_LEAGUE_RIDER_MENU_H
#define MOTOGP_FANTASY_LEAGUE_RIDER_MENU_H

#include <iostream>
#include "menu.h"

class RiderMenu {
private:
    MemberList *memberList;
    string seasonName;
    bool saveChanges;
public:
    RiderMenu(MemberList *memberList, string &seasonName);

    void menu();
    bool addRider();
    bool modifyRider();
    bool deleteRider();
    void listRiders();
    void saveChangesMade();

    void enterToContinue();
};

enum{
    ADD_RIDER = 1,
    MODIFY_RIDER,
    DELETE_RIDER,
    LIST_RIDERS,
    DELETE_ALL_RIDERS,
    SAVE_CHANGES_RIDERS,
    EXIT_RIDER
};

#endif //MOTOGP_FANTASY_LEAGUE_RIDER_MENU_H
