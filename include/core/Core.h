#ifndef MOTOGP_FANTASY_LEAGUE_MODERN_CORE_H
#define MOTOGP_FANTASY_LEAGUE_MODERN_CORE_H

#include <iostream>

#include "ui/Menu.h"
#include "core/Logger.h"
#include "views/RiderManagerList.h"
#include "views/MemberList.h"
#include "utils/Util.h"

class Core {
private:
    std::shared_ptr<Logger> m_Logger = std::make_shared<Logger>();
    Menu m_Menu;
    std::string m_SelectedSeason;
public:
    Core();

    void InitializeCore();
    void FirstStart();
};


#endif //MOTOGP_FANTASY_LEAGUE_MODERN_CORE_H
