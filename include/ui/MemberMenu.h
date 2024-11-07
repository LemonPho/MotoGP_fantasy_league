#ifndef MOTOGP_FANTASY_LEAGUE_MODERN_MEMBERMENU_H
#define MOTOGP_FANTASY_LEAGUE_MODERN_MEMBERMENU_H

#include <iostream>
#include <memory>
#include <algorithm>

#include "views/MemberList.h"
#include "views/RiderManagerList.h"
#include "core/Logger.h"
#include "utils/Util.h"
#include "ui/DynamicUi/DynamicUi.h"
#include "ui/DynamicUi/MemberSelectorUi.h"
#include "ui/DynamicUi/RidersSelectorUi.h"

class MemberMenu {
private:
    RiderManagerList m_RiderManagerList;
    MemberList m_MemberList;
    std::shared_ptr<Logger> m_Logger;
    std::string m_SelectedSeason;
public:
    MemberMenu();
    explicit MemberMenu(std::shared_ptr<Logger> logger);

    void InitializeMemberMenu();

    void Menu();
    bool AddMember();
    bool DeleteMember();
    bool ModifyMember();

    int OptionSelector(const std::string &option);
};

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

namespace ADD_MEMBER_SPACING{
    const int LEFT_ARROW_SPACING = 10;
    const int RIGHT_ARROW_SPACING = 19;
    const int LINE_OPTION_SPACING = 7;
    const int MESSAGE_LINE_SPACING = 9;
    const int MESSAGE_START_SPACING = 10;
    const int ACCEPT_LINE_SPACING = 1;
}

namespace DELETE_MEMBER_SPACING{
    const int LEFT_ARROW_SPACING = 10;
    const int RIGHT_ARROW_SPACING = 19;
    const int LINE_OPTION_SPACING = 7;
    const int ACCEPT_LINE_SPACING = 1;
}


#endif //MOTOGP_FANTASY_LEAGUE_MODERN_MEMBERMENU_H
