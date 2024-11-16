#include "ui/DynamicUi/DynamicUi.h"

DynamicUi::DynamicUi(std::shared_ptr<Logger> logger, std::vector<std::shared_ptr<BaseUiElement>>& uiElements, std::string label) : m_Logger(logger), m_UiElements(uiElements) {
    m_Logger->Log("Initializing" + label + " ui", Logger::LogLevelInfo, Logger::LogFile);
    m_Label = label;
    m_Terminate = std::make_shared<bool>(false);
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
    BaseUiElement::Coordinates coordinates = uiElement.GetCoordinates();
    
    std::string clearString(size.width, ' ');
    for (int i = coordinates.top; i <= coordinates.bottom; i++) {
        std::cout << clearString;
    }
}

bool DynamicUi::GetChangesMade() {
    return m_ChangesMade;
}

void DynamicUi::InitializeUi() {
    system(CLEAR);
    m_Logger->Log("Starting " + m_Label + " ui", Logger::LogLevelInfo, Logger::LogFile);

    *m_Terminate = false;
    //disabling cursor
    ToggleConsoleCursor(false);

    //getting window dimensions (terminal)
    GetWindowDimensions(m_Window.columns, m_Window.rows);

    //configuring elements
    size_t longestString;
    size_t rowCounter = 1;
    for (auto& uiElement : m_UiElements) {
        uiElement->InitializeUiElement(m_Window, rowCounter);
        uiElement->SetTerminate(m_Terminate);
        rowCounter = uiElement->GetCoordinates().bottom;
    }

    //configuring selected element
    for(int i = 0; i < m_UiElements.size(); i++){
        if (!m_UiElements[i]->GetStatic()) {
            m_SelectedElement = i;
            break;
        }
    }

    char key = 0;
    //display instructions and menu
    Display();
    while (*m_Terminate == false) {
        if (key == keys::LEFT_KEY || key == keys::RIGHT_KEY) {
            Display();
        } else {
            UpdateDisplay();
        }
        key = util::CustomGetch();
        Navigate(key);
    }

    ToggleConsoleCursor(true);
}

void DynamicUi::Display(){
    system(CLEAR);

    for (int i = 0; i < m_UiElements.size(); i++) {
        if (m_UiElements[i]->GetCoordinates().top > m_Window.rows) {
            break;
        }

        if (i == m_SelectedElement && !m_UiElements[m_SelectedElement]->GetStatic()) {
            DrawElementOutline(*m_UiElements[i]);
        }

        m_UiElements[i]->Display();
    }

    for (auto& uiElement : m_UiElements) {
        
        uiElement->Display();
    }
}

void DynamicUi::UpdateDisplay() {

}

void DynamicUi::RemoveElementOutline(BaseUiElement& uiElement) {
    //top left corner
    gotoxy(uiElement.GetCoordinates().left, uiElement.GetCoordinates().top);
    std::cout << " ";

    //bottom left corner
    gotoxy(uiElement.GetCoordinates().left, uiElement.GetCoordinates().bottom);
    std::cout << " ";

    //bottom right corner
    gotoxy(uiElement.GetCoordinates().right, uiElement.GetCoordinates().bottom);
    std::cout << " ";

    //top right corner
    gotoxy(uiElement.GetCoordinates().right, uiElement.GetCoordinates().top);
    std::cout << " ";
}

void DynamicUi::DrawElementOutline(BaseUiElement& uiElement) {    
    //top left corner
    gotoxy(uiElement.GetCoordinates().left, uiElement.GetCoordinates().top);
    std::cout << char(218);

    //bottom left corner
    gotoxy(uiElement.GetCoordinates().left, uiElement.GetCoordinates().bottom);
    std::cout << char(192);

    //bottom right corner
    gotoxy(uiElement.GetCoordinates().right, uiElement.GetCoordinates().bottom);
    std::cout << char(217);

    //top right corner
    gotoxy(uiElement.GetCoordinates().right, uiElement.GetCoordinates().top);
    std::cout << char(191);

    /*
    //building vertical lines
    for (int i = uiElement.GetCoordinates().y + 1; i < uiElement.GetCoordinates().y + uiElement.GetSize().height - 2; i++) {
        gotoxy(i, uiElement.GetCoordinates().x);
        std::cout << char(179);
        gotoxy(i, uiElement.GetCoordinates().x + uiElement.GetSize().width);
        std::cout << char(179);
    }

    for (int i = uiElement.GetCoordinates().x + 1; i < uiElement.GetCoordinates().x + uiElement.GetSize().width - 2; i++) {
        gotoxy(uiElement.GetCoordinates().y, i);
        std::cout << char(196);
        gotoxy(uiElement.GetCoordinates().y + uiElement.GetSize().height, i);
        std::cout << char(196);
    }*/
}

void DynamicUi::PrintLog() {
    //int messageLine = GetSelectionsSpace().upperLimit - UiSpacing::MESSAGE_LINE_SPACING;
    //Clear message line
    //ClearLine(messageLine);

    //Print new message
    //gotoxy(0, messageLine); 
    m_Logger->PrintLog();
}

void DynamicUi::Navigate(const char key) {
    switch (key) {
        case keys::UP_KEY: {
            if(!m_UiElements[m_SelectedElement]->GetStatic())
                m_UiElements[m_SelectedElement]->OnKeyUp();
            break;
        }

        case keys::DOWN_KEY: {
            if (!m_UiElements[m_SelectedElement]->GetStatic())
                m_UiElements[m_SelectedElement]->OnKeyDown();
            break;
        }

        case keys::TAB_KEY: {
            int previousSelected = m_SelectedElement;
            RemoveElementOutline(*m_UiElements[m_SelectedElement]);
            m_SelectedElement++;
            while (m_UiElements[m_SelectedElement]->GetStatic() && previousSelected != m_SelectedElement) {
                m_SelectedElement++;
                m_SelectedElement %= m_UiElements.size();
            }
            if(!m_UiElements[m_SelectedElement]->GetStatic())
                DrawElementOutline(*m_UiElements[m_SelectedElement]);
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
            if (!m_UiElements[m_SelectedElement]->GetStatic()) {
                m_UiElements[m_SelectedElement]->OnSelect();
            }
            break;
        }

        case keys::BACKSPACE_KEY: {
            if (!m_UiElements[m_SelectedElement]->GetStatic()) {
                m_UiElements[m_SelectedElement]->OnDeselect();
            }
            break;
        }

        case keys::Q_KEY: {
            m_Logger->Log("Exiting Ui by cancelation", Logger::LogLevelInfo, Logger::LogFile);
            *m_Terminate = true;
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
    *m_Terminate = true;
}

