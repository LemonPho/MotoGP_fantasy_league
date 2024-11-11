#ifndef MOTOGP_FANTASY_LEAGUE_MODERN_MEMBERMENU_H
#define MOTOGP_FANTASY_LEAGUE_MODERN_MEMBERMENU_H

#include <iostream>
#include <memory>
#include <algorithm>

#include "views/MemberList.h"
#include "views/RiderManagerList.h"
#include "core/Logger.h"
#include "utils/Util.h"
#include "ui/DynamicUi/LimitedSelectionUi.h"
#include "ui/DynamicUi/MultipleSelectionUi.h"
#include "ui/DynamicUi/RidersSelectorUi.h"
#include "ui/DynamicUi/SingleSelectionUi.h"
#include "models/Season.h"

class MemberMenu {
public:
    enum options {
        ADD_MEMBER = 0,
        DELETE_MEMBER,
        MODIFY_MEMBER,
        SHOW_MEMBERS,
        DELETE_ALL_MEMBERS,
        CREATE_STANDINGS_FILE,
        SAVE_CHANGES,
        EXIT,
    };
private:
    std::shared_ptr<Logger> m_Logger;
    std::shared_ptr<Season> m_Season;
public:
    MemberMenu();

    void InitializeMemberMenu(std::shared_ptr<Logger> logger, std::shared_ptr<Season> season);

    void Menu();
    bool AddMember();
    bool DeleteMember();
    bool ModifyMember();
};


#endif //MOTOGP_FANTASY_LEAGUE_MODERN_MEMBERMENU_H
