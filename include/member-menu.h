#ifndef MOTOGP_FANTASY_LEAGUE_MEMBER_MENU_H
#define MOTOGP_FANTASY_LEAGUE_MEMBER_MENU_H

#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>

#include "member-list.h"
#include "error-message.h"

using namespace std;

class MemberMenu {
    private:
        MemberList* memberList;
        RiderList* riderList;
        string seasonName;
        bool saveChanges;

        ErrorMessage *errorMessage;
    public:
        MemberMenu(MemberList *memberList, RiderList *riderList, string &seasonName, ErrorMessage *errorMessage);

        void menu();
        bool addMember();
        bool deleteMember();
        bool modifyMember();

        int optionSelector(string option);
};

enum{
    ADD_MEMBER = 1,
    DELETE_MEMBER,
    MODIFY_MEMBER,
    LIST_MEMBERS,
    DELETE_ALL_MEMBERS,
    CREATE_STANDINGS_FILE,
    SAVE_CHANGES_MEMBER,
    EXIT_MEMBER
};

enum{
    CHANGE_USERNAME = 1,
    CHANGE_RIDER,
    EXIT_MODIFY
};

#endif //MOTOGP_FANTASY_LEAGUE_MEMBER_MENU_H
