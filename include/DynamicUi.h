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

    size_t m_HighLightedOption = 0;
    size_t m_SelectedOption = 0;

    //implement mod operator for menu out of bounds

    void gotoxy(size_t x, size_t y);
    int CheckIfSelected();

public:
    DynamicUi(std::shared_ptr<Logger> logger, std::vector<std::string>& instructions, std::vector<std::string>& menuOptions);

    void StartUi();
    void Display();
    void Navigate();
    virtual void OnSelect();
    virtual void OnDeselect();
    virtual void OnCancel();


};


#endif //MOTOGP_FANTASY_LEAGUE_MODERN_DYNAMICUI_H
