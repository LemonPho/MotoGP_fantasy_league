#ifndef MOTOGP_FANTASY_LEAGUE_MODERN_MEMBERMENU_H
#define MOTOGP_FANTASY_LEAGUE_MODERN_MEMBERMENU_H

#include <iostream>
#include <memory>

#include "MemberList.h"
#include "RiderManagerList.h"
#include "Logger.h"
#include "Util.h"

class MemberMenu {
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

#ifdef _WIN32
enum keys{
    UP_KEY = 80,
    DOWN_KEY = 72,
    ENTER_KEY = 13,
    BACKSPACE_KEY = 8,
    Q_KEY = 113,
};
#else
enum keys{
    UP_KEY = 66,
    DOWN_KEY = 65,
    ENTER_KEY = 10,
    BACKSPACE_KEY = 127,
    Q_KEY = 113,
};
#endif

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

enum addMember{
    LEFT_ARROW_SPACING = 10,
    RIGHT_ARROW_SPACING = 19,
    LINE_OPTION_SPACING = 6,
    MESSAGE_LINE_SPACING = 8,
    MESSAGE_START_SPACING = 10,
    ACCEPT_LINE_SPACING = 1,
};


#endif //MOTOGP_FANTASY_LEAGUE_MODERN_MEMBERMENU_H
