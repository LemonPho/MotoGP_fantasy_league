#ifndef MOTOGP_FANTASY_LEAGUE_MODERN_DYNAMICUI_H
#define MOTOGP_FANTASY_LEAGUE_MODERN_DYNAMICUI_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <utility>

#include "core/Logger.h"
#include "utils/Util.h"

struct Window {
    int columns=0;
    int rows=0;
};

struct SelectionsSpace {
    size_t upperLimit = 0;
    size_t lowerLimit = 0;
};

class DynamicUi {
// This is the base of what the dynamic ui needs to sort of work, it is lacking a selections array (located in its children classes)
// and OnSelect() and OnDeselect() are empty (built in child classes)
private:
    std::shared_ptr<Logger> m_Logger;

    std::vector<std::string> &m_Instructions;
    std::vector<std::string> &m_MenuOptions;
    
    size_t m_InstructionsLength = 0;
    size_t m_LongestMenuOption = 0;
    size_t m_OptionCount = 0;

    SelectionsSpace m_SelectionsSpace;

    size_t m_LeftArrow, m_RightArrow;
    size_t m_HighlightedOption = 0;
    size_t m_OptionIndex = 0;


    bool m_Terminate = false;
    bool m_ChangesMade = false;
protected:
    Window m_Window;
    void gotoxy(size_t x, size_t y);
    void GetWindowDimensions(int& columns, int& rows);
    void ToggleConsoleCursor(bool enable);
    void UpdateArrowPosition(size_t line, size_t left, size_t right);
    void ClearText(size_t start, size_t end, size_t left, size_t right);
    void ClearLine(size_t line);
public:
    DynamicUi(std::shared_ptr<Logger> logger, std::vector<std::string>& instructions, std::vector<std::string>& menuOptions);

    std::vector<std::string>& GetMenuOptions();
    size_t GetLongestMenuOption();
    size_t GetHighlightedOption();
    size_t GetOptionCount();
    size_t GetOptionIndex();
    size_t GetInstructionsLength();
    size_t GetLeftArrow();
    size_t GetRightArrow();
    bool GetChangesMade();
    SelectionsSpace GetSelectionsSpace();

    void InitializeUi();
    void Display();
    void PrintLog();
    virtual bool PrintAccept(size_t x, size_t y);
    void Navigate(const char key);
    virtual void OnSelect();
    virtual void OnDeselect();
    virtual void Exit(bool changesMade);
   
    virtual ~DynamicUi() = default;
};

enum UiSpacing {
    INSTRUCTIONS_DOWN_SPACING = 2,
    ARROWS_SPACING = 3,
    SELECT_SPACING = 7,
    ACCEPT_LINE_SPACING = 1,
    MESSAGE_LINE_SPACING = 1,
};

#ifdef _WIN32
enum keys {
    UP_KEY = 80,
    DOWN_KEY = 72,
    ENTER_KEY = 13,
    BACKSPACE_KEY = 8,
    Q_KEY = 113,
};
#else
enum keys {
    UP_KEY = 66,
    DOWN_KEY = 65,
    ENTER_KEY = 10,
    BACKSPACE_KEY = 127,
    Q_KEY = 113,
};
#endif


#endif //MOTOGP_FANTASY_LEAGUE_MODERN_DYNAMICUI_H
