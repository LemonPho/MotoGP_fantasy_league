#ifndef MOTOGP_FANTASY_LEAGUE_MODERN_DYNAMICUI_H
#define MOTOGP_FANTASY_LEAGUE_MODERN_DYNAMICUI_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <utility>

#include "Logger.h"

class DynamicUi {
private:
    std::shared_ptr<Logger> m_Logger;

    std::vector<std::string> &m_Instructions;
    std::vector<std::string> &m_MenuOptions;

    //implement mod operator for menu out of bounds

public:
    DynamicUi(std::shared_ptr<Logger> logger, std::vector<std::string>& instructions, std::vector<std::string>& menuOptions);


};


#endif //MOTOGP_FANTASY_LEAGUE_MODERN_DYNAMICUI_H
