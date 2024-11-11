/*
#include "ui/DynamicUi/RidersSelectorUi.h"

RidersSelectorUi::RidersSelectorUi(std::shared_ptr<Logger> logger, std::vector<std::string>& instructions, std::vector<std::string>& menuOptions) : DynamicUi(logger, instructions, menuOptions) {
    m_Logger = logger;
}

int RidersSelectorUi::CheckIfSelected(size_t query) {
    int selection = -1;

    for (int i = 0; i < Member::RIDER_COUNT; i++) {
        if (m_Selections[i] == query) {
            selection = i;
        }
    }

    return selection;
}

int RidersSelectorUi::GetEmptySpotSelections() {
    for (int i = 0; i < Member::RIDER_COUNT; i++) {
        if (m_Selections[i] == -1) {
            return i;
        }
    }

    return -1;
}

std::vector<int>& RidersSelectorUi::GetSelections() {
    return m_Selections;
}

void RidersSelectorUi::OnSelect() {
    //User selected the accept line
    if (GetHighlightedOption() == GetSelectionsSpace().lowerLimit) {
        //Correct amount of riders selected
        if (m_SelectionCount == Member::RIDER_COUNT) {
            Exit(true);
        } else {
            //Incorrect amount of riders selected
            m_Logger->Log("You must select 6 riders", Logger::LogLevelInfo, Logger::LogConsole);
            m_Logger->Log("User tried to save " + std::to_string(m_SelectionCount) + " riders, 6 required", Logger::LogLevelError, Logger::LogFile);
        }
        return;
    }

    //Shouldn't happen, but in that case will just close the menu, although its more likely that a segmentation error occurs
    if (m_SelectionCount > Member::RIDER_COUNT) {
        m_Logger->Log("More than the max amount of riders were selected, exiting", Logger::LogLevelError, Logger::LogConsoleFile);
        Exit(false);
        return;
    }

    //User tried to add more than six riders
    if (m_SelectionCount == Member::RIDER_COUNT) {
        m_Logger->Log("You have selected the max amount of riders", Logger::LogLevelInfo, Logger::LogConsole);
        return;
    }

    int emptyIndex = GetEmptySpotSelections();

    //5 == independent rider
    if (emptyIndex == 5) {
        m_Selections[emptyIndex] = GetOptionIndex();
        if (CheckIfSelected(GetOptionIndex()) != -1) {
            gotoxy(GetRightArrow() + 7, GetHighlightedOption());
        } else {
            gotoxy(GetRightArrow() + 5, GetHighlightedOption());
        }

        std::cout << "i";
        m_SelectionCount++;
        return;
    }

    //User successfully selected a rider that isn't in the list yet
    if (CheckIfSelected(GetOptionIndex()) == -1) {
        //this shouldn't end up happening since we already checked if 6 riders are selected
        if (emptyIndex == -1) {
            m_Logger->Log("List is full while selectionCount says its not full, exiting", Logger::LogLevelError, Logger::LogFile);
            m_Logger->Log("There was an error while selecting riders, please try again", Logger::LogLevelError, Logger::LogConsole);
            Exit(false);
            return;
        }

        m_Selections[emptyIndex] = GetOptionIndex();
        gotoxy(GetRightArrow() + 5, GetHighlightedOption());


        std::cout << emptyIndex + 1;
        m_SelectionCount++;

        m_Logger->Log("Selected rider", Logger::LogLevelInfo, Logger::LogFile);

        return;
    }
}

void RidersSelectorUi::OnDeselect() {
    int selected = CheckIfSelected(GetOptionIndex());
    if (selected == -1) {
        return;
    }

    if (selected == 5) {
        gotoxy(GetRightArrow() + 7, GetHighlightedOption());
        std::cout << " ";
    } else {
        gotoxy(GetRightArrow() + 5, GetHighlightedOption());
        std::cout << " ";
    }

    m_Logger->Log("Removed rider", Logger::LogLevelInfo, Logger::LogFile);
    m_Selections[selected] = -1;
    m_SelectionCount--;
}
*/