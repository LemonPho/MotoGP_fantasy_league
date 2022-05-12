#ifndef MOTOGP_FANTASY_LEAGUE_MEMBER_MENU_H
#define MOTOGP_FANTASY_LEAGUE_MEMBER_MENU_H

#include <iostream>

#include "member-list.h"

using namespace std;

class MemberMenu {
private:
    MemberList* memberList;
    string seasonName;
    bool saveChanges;
public:
    MemberMenu(MemberList *memberList, string &seasonName);

    void menu();
    void addMember();
    void deleteMember();
    void modifyMember();
    void saveChangesMade();

    void enterToContinue();
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

#endif //MOTOGP_FANTASY_LEAGUE_MEMBER_MENU_H
