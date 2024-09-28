#ifndef MOTOGP_FANTASY_LEAGUE_MODERN_DYNAMICUI_H
#define MOTOGP_FANTASY_LEAGUE_MODERN_DYNAMICUI_H

#include <iostream>
#include <vector>
#include <memory>

#include "Logger.h"

class DynamicUi {
private:
    std::shared_ptr<Logger> m_Logger;

    std::vector<std::string> m_Instructions;
    std::vector<std::string> m_MenuOptions;
    size_t m_SelectedOption;
    size_t m_CurrentLine;
    size_t longestOption;

    //implement mod operator for menu out of bounds

public:
    DynamicUi();
    explicit DynamicUi(std::shared_ptr<Logger> logger);
    DynamicUi(std::shared_ptr<Logger> logger, std::vector<std::string>& instructions, std::vector<std::string>& menuOptions);


};


#endif //MOTOGP_FANTASY_LEAGUE_MODERN_DYNAMICUI_H
