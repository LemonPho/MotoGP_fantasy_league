#ifndef MOTOGP_FANTASY_LEAGUE_MODERN_MEMBERMENU_H
#define MOTOGP_FANTASY_LEAGUE_MODERN_MEMBERMENU_H

#include <iostream>
#include <memory>

#include "MemberList.h"
#include "RiderManagerList.h"
#include "Logger.h"
#include "Util.h"

class MemberMenu {
public:
    enum options{
        INVALID_OPTION = 0,
        ADD_MEMBER = 1,
        DELETE_MEMBER,
        MODIFY_MEMBER,
        SHOW_MEMBERS,
        DELETE_ALL_MEMBERS,
        CREATE_STANDINGS_FILE,
        SAVE_CHANGES,
        EXIT,
    };
private:
    RiderManagerList m_RiderManagerList;
    MemberList m_MemberList;
    std::shared_ptr<Logger> m_Logger;
    std::string m_SelectedSeason;
public:
    MemberMenu();
    MemberMenu(std::shared_ptr<Logger> logger);

    void InitializeMemberMenu();

    void Menu();
    bool AddMember();
    bool DeleteMember();
    bool ShowMembers();
    bool ModifyMember();

    int OptionSelector(const std::string &option);
};


#endif //MOTOGP_FANTASY_LEAGUE_MODERN_MEMBERMENU_H
