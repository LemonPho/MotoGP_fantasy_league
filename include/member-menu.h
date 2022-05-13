#ifndef MOTOGP_FANTASY_LEAGUE_MEMBER_MENU_H
#define MOTOGP_FANTASY_LEAGUE_MEMBER_MENU_H

#include <iostream>

#include "member-list.h"

using namespace std;

class MemberMenu {
private:
    MemberList* memberList;
    RiderList* riderList;
    string seasonName;
    bool saveChanges;
public:
    MemberMenu(MemberList *memberList, RiderList *riderList, string &seasonName);

    void updateMemberPoints();

    void menu();
    bool addMember();
    bool deleteMember();
    void modifyMember();

    static void enterToContinue();
};

enum{
    ADD_MEMBER = 1,
    DELETE_MEMBER,
    MODIFY_MEMBER,
    LIST_MEMBERS,
    DELETE_ALL_MEMBERS,
    SAVE_CHANGES_MEMBER,
    EXIT_MEMBER
};

enum{
    CHANGE_USERNAME = 1,
    CHANGE_RIDER,
    CHANGE_ROOKIE,
    SAVE_CHANGES_MODIFY,
    EXIT_MODIFY
};

#endif //MOTOGP_FANTASY_LEAGUE_MEMBER_MENU_H
