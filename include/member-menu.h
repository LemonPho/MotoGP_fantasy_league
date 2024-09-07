#ifndef MOTOGP_FANTASY_LEAGUE_MEMBER_MENU_H
#define MOTOGP_FANTASY_LEAGUE_MEMBER_MENU_H

#include <iostream>
#include <fstream>
#include <ncurses.h>
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

#ifdef _WIN32
enum{
    UP_KEY = 72,
    DOWN_KEY = 80,
    ENTER_KEY = 13,
    BACKSPACE_KEY = 8,
};
#else
enum{
    UP_KEY = 66,
    DOWN_KEY = 65,
    ENTER_KEY = 10,
    BACKSPACE_KEY = 127,
};
#endif

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
