#ifndef MOTOGP_FANTASY_LEAGUE_MODERN_DYNAMICUI_H
#define MOTOGP_FANTASY_LEAGUE_MODERN_DYNAMICUI_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <utility>

#include "core/Logger.h"
#include "utils/Util.h"
#include "DynamicUiElement/BaseUiElement.h"
#include "Window.h"

class DynamicUi {
public:
    enum class Positioning {
        LEFT=0,
        CENTER,
        RIGHT,
    };
// This is the base of what the dynamic ui needs to sort of work, it is lacking a selections array (located in its children classes)
// and OnSelect() and OnDeselect() are empty (built in child classes)
private:
    std::shared_ptr<Logger> m_Logger;

    std::string m_Label;
    std::vector<std::shared_ptr<BaseUiElement>> m_UiElements;

    size_t m_SelectedElement = 0;
    int m_CurrentPage = 0;
    size_t m_PageCount = 1;

    std::shared_ptr<bool> m_Terminate;
    bool m_ChangesMade = false;
protected:
    Window m_Window;
    void gotoxy(size_t x, size_t y);
    void GetWindowDimensions(int& columns, int& rows);
    void ToggleConsoleCursor(bool enable);
    void UpdateHighlightPosition(size_t line, size_t left, size_t right);
    void ClearText(size_t start, size_t end, size_t left, size_t right);
    void ClearLine(size_t line);
    void ClearUiElement(BaseUiElement& uiElement);
public:
    DynamicUi(std::shared_ptr<Logger> logger, std::vector<std::shared_ptr<BaseUiElement>>& uiElements, std::string label);

    bool GetChangesMade();
    //TODO: create function that only clears an elements area

    void InitializeUi();
    void Display();
    void UpdateDisplay();
    void RemoveElementOutline(BaseUiElement& uiElement);
    void DrawElementOutline(BaseUiElement& uiElement);
    void PrintLog();
    void Navigate(const char key);
    virtual void OnSelect();
    virtual void OnDeselect();
    virtual void Exit(bool changesMade);
   
    virtual ~DynamicUi() = default;
};

#ifdef _WIN32
enum keys {
    UP_KEY = 72,
    DOWN_KEY = 80,
    RIGHT_KEY = 77,
    LEFT_KEY = 75,
    ENTER_KEY = 13,
    BACKSPACE_KEY = 8,
    Q_KEY = 113,
    TAB_KEY = 9,
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
