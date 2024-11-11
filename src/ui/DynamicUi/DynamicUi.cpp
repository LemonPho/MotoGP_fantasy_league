#include "ui/DynamicUi/DynamicUi.h"

DynamicUi::DynamicUi(std::shared_ptr<Logger> logger, std::vector<std::shared_ptr<BaseUiElement>>& uiElements, std::string label) : m_Logger(logger), m_UiElements(uiElements) {
    m_Logger->Log("Initializing" + label + " ui", Logger::LogLevelInfo, Logger::LogFile);
    m_Label = label;
}

void DynamicUi::gotoxy(size_t x, size_t y) {
    std::cout << "\033[" << y << ";" << x << "H";
}

void DynamicUi::GetWindowDimensions(int& columns, int& rows) {
    m_Logger->Log("Getting console window dimensions", Logger::LogLevelInfo, Logger::LogFile);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        // The number of columns (width)
        columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        // The number of rows (height)
        rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
    else {
        // If the function fails, return some default value
        columns = 80;
        rows = 25;
    }
}

void DynamicUi::ToggleConsoleCursor(bool enable) {
    m_Logger->Log("Disabling console cursor", Logger::LogLevelInfo, Logger::LogFile);
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = enable; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}


void DynamicUi::UpdateHighlightPosition(size_t line, size_t left, size_t right) {
    gotoxy(left, line);
    std::cout << "->";
    gotoxy(right, line);
    std::cout << "<-";
}

void DynamicUi::ClearText(size_t start, size_t end, size_t left, size_t right) {
    for (size_t i = start; i <= end; i++) {
        gotoxy(left, i);
        std::cout << "  ";
        gotoxy(right, i);
        std::cout << "  ";
    }
}

void DynamicUi::ClearLine(size_t line) {
    std::string string(m_Window.columns, ' ');
    gotoxy(0, line);
    std::cout << string;
}

void DynamicUi::ClearUiElement(BaseUiElement& uiElement) {
    BaseUiElement::Size size = uiElement.GetSize();
    BaseUiElement::Coordinate coordinates = uiElement.GetCoordinates();
    
    std::string clearString(size.width, ' ');
    for (int i = coordinates.y; i <= coordinates.y + size.height; i++) {
        std::cout << clearString;
    }
}

bool DynamicUi::GetChangesMade() {
    return m_ChangesMade;
}

void DynamicUi::InitializeUi() {
    system(CLEAR);
    m_Logger->Log("Starting " + m_Label + " ui", Logger::LogLevelInfo, Logger::LogFile);

    m_Terminate = false;
    //disabling cursor
    ToggleConsoleCursor(false);

    //getting window dimensions (terminal)
    GetWindowDimensions(m_Window.columns, m_Window.rows);

    //configuring elements
    size_t longestString;
    size_t rowCounter = 1;
    for (auto& element : m_Elements) {
        element.y = rowCounter;
        longestString = 0;
        for (auto& string : element.content) {
            if (string.length() > longestString) {
                longestString = string.length();
            }
            rowCounter++;
            if (rowCounter >= m_Window.rows - UiSpacing::FOOTER_SPACING) {
                rowCounter = 0;
                if (element.content.size() < m_Window.rows) {
                    element.y = rowCounter;
                }
                m_PageCount++;
            }
        }
        
        if (element.positioning == POSITIONING_LEFT) {
            element.x = 0;
        } else if(element.positioning == POSITIONING_CENTER) {
            element.x = (m_Window.columns / 2) - (longestString / 2) - UiSpacing::HIGHLIGHT_SPACING;
        } else if (element.positioning == POSITIONING_RIGHT) {
            element.x = m_Window.columns - longestString - UiSpacing::HIGHLIGHT_SPACING;
        }
        element.highlightWidth = longestString + UiSpacing::HIGHLIGHT_SPACING;
        element.page = m_PageCount;
    }

    char key = 0;
    //display instructions and menu
    Display();
    while (!m_Terminate) {
        if (key == keys::LEFT_KEY || key == keys::RIGHT_KEY) {
            Display();
        } else {
            UpdateDisplay();
        }
        PrintLog();
        key = util::CustomGetch();
        Navigate(key);
    }

    ToggleConsoleCursor(true);
}

void DynamicUi::Display(){
    size_t centeredText;
    size_t i = m_InstructionsLength + UiSpacing::INSTRUCTIONS_DOWN_SPACING;
    std::string accept = "Accept";

    system(CLEAR);

    for (const auto& instruction : m_Instructions) {
        std::cout << instruction << std::endl;
    }

    if (m_Pagination) {
        size_t start = m_CurrentPage * (m_SelectionsSpace.lowerLimit - m_SelectionsSpace.upperLimit);
        size_t end = ((m_CurrentPage + 1) * (m_SelectionsSpace.lowerLimit - m_SelectionsSpace.upperLimit) > m_MenuOptions.size()) ? m_MenuOptions.size() : (m_CurrentPage+1) * (m_SelectionsSpace.lowerLimit - m_SelectionsSpace.upperLimit);
        for (size_t j = start; j < end; j++) {
            centeredText = m_Window.columns / 2 - m_MenuOptions[j].length() / 2;
            gotoxy(centeredText, i);
            i++;
            std::cout << m_MenuOptions[j];
        }
    } else {
        for (const auto& menuOption : m_MenuOptions) {
            centeredText = m_Window.columns / 2 - menuOption.length() / 2;
            gotoxy(centeredText, i);
            i++;
            std::cout << menuOption;
        }
    }

    centeredText = m_Window.columns / 2 - accept.length() / 2;
    m_AcceptPrinted = PrintAccept(centeredText, i);
    if (!m_AcceptPrinted) {
        m_SelectionsSpace.lowerLimit = m_OptionCount + m_InstructionsLength + UiSpacing::INSTRUCTIONS_DOWN_SPACING - 1;
    }

    if (m_Pagination) {
        std::string pageString = "[" + std::to_string(m_CurrentPage + 1) + "/" + std::to_string(m_PageCount) + "]";
        centeredText = m_Window.columns / 2 - pageString.length() / 2;
        gotoxy(centeredText, m_Window.rows);
        std::cout << pageString;
    }
}

void DynamicUi::UpdateDisplay() {

}

void DynamicUi::PrintLog() {
    int messageLine = GetSelectionsSpace().upperLimit - UiSpacing::MESSAGE_LINE_SPACING;
    //Clear message line
    ClearLine(messageLine);

    //Print new message
    gotoxy(0, messageLine); 
    m_Logger->PrintLog();
}

bool DynamicUi::PrintAccept(size_t x, size_t y){
    gotoxy(x, y);
    std::cout << "\x1b[32m" << "Accept" << "\033[0m";
    return true;
}

void DynamicUi::Navigate(const char key) {
    switch (key) {
        case keys::UP_KEY: {
            std::cout << m_OptionIndex << " " << m_HighlightedOption;
            m_OptionIndex--;
            if (m_AcceptPrinted) {
                m_OptionIndex %= m_OptionCount + UiSpacing::ACCEPT_LINE_SPACING;
            } else {
                m_OptionIndex %= m_OptionCount;
            }
            m_HighlightedOption = m_InstructionsLength + UiSpacing::INSTRUCTIONS_DOWN_SPACING + m_OptionIndex;
            break;
        }

        case keys::DOWN_KEY: {
            std::cout << m_OptionIndex << " " << m_HighlightedOption;
            m_HighlightedOption++;
            if (m_HighlightedOption > m_SelectionsSpace.lowerLimit) {
                m_HighlightedOption = m_SelectionsSpace.upperLimit;
            }
            m_OptionIndex++;
            if (m_AcceptPrinted) {
                m_OptionIndex %= m_OptionCount + UiSpacing::ACCEPT_LINE_SPACING;
            } else {
                m_OptionIndex %= m_OptionCount;
            }
            break;
        }

        case keys::RIGHT_KEY: {
            m_CurrentPage++;
            m_CurrentPage %= m_PageCount;
            break;
        }

        case keys::LEFT_KEY: {
            m_CurrentPage--;
            if (m_CurrentPage < 0) {
                m_CurrentPage = m_PageCount - 1;
            }
            break;
        }

        case keys::ENTER_KEY: {
            OnSelect();
            break;
        }

        case keys::BACKSPACE_KEY: {
            OnDeselect();
            break;
        }

        case keys::Q_KEY: {
            m_Logger->Log("Exiting Ui by cancelation", Logger::LogLevelInfo, Logger::LogFile);
            m_Terminate = true;
            m_ChangesMade = false;
            break;
        }
    }
}

//These two functions are to be completely built by the user
void DynamicUi::OnSelect() {
    return;
}

void DynamicUi::OnDeselect() {
    return;
}

void DynamicUi::Exit(bool changesMade) {
    m_ChangesMade = changesMade;

    if (m_ChangesMade) {
        m_Logger->Log("User exiting menu by accepting", Logger::LogLevelInfo, Logger::LogFile);
    } else {
        m_Logger->Log("User exiting menu by cancelling", Logger::LogLevelInfo, Logger::LogFile);
    }
    m_Terminate = true;
}

