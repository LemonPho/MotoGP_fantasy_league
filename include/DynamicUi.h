#ifndef MOTOGP_FANTASY_LEAGUE_MODERN_DYNAMICUI_H
#define MOTOGP_FANTASY_LEAGUE_MODERN_DYNAMICUI_H

#include <iostream>
#include <vector>

class DynamicUi {
private:
    std::vector<std::string> m_Instructions;
    std::vector<std::string> m_MenuOptions;
    int m_SelectedOption;
    int m_CurrentLine;
    std::string longestOption;
    
};


#endif //MOTOGP_FANTASY_LEAGUE_MODERN_DYNAMICUI_H
