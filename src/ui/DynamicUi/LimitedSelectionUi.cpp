/*
#include "ui/DynamicUi/LimitedSelectionUi.h"

int LimitedSelectionUi::CheckIfSelected(size_t query) {
	for (int i = 0; i < m_MaxSelections; i++) {
		if (m_Selections[i] == query) {
			return i;
		}
	}

	return -1;
}

int LimitedSelectionUi::GetEmptySpotSelections() {
	for (int i = 0; i < m_MaxSelections; i++) {
		if (m_Selections[i] == -1) {
			return i;
		}
	}

	return -1;
}

LimitedSelectionUi::LimitedSelectionUi(std::shared_ptr<Logger> logger, std::vector<std::string>& instructions, std::vector<std::string>& menuOptions, std::vector<std::string>& selectionsCharacters) : DynamicUi(logger, instructions, menuOptions) {
	m_Logger = logger;
	m_Selections.resize(selectionsCharacters.size());
	std::fill(m_Selections.begin(), m_Selections.end(), -1);
    m_SelectionsCharacters = selectionsCharacters;
	m_MaxSelections = selectionsCharacters.size();
}

std::vector<int> LimitedSelectionUi::GetSelections() {
	return m_Selections;
}

void LimitedSelectionUi::OnSelect() {
    //User selected the accept line
    if (GetHighlightedOption() == GetSelectionsSpace().lowerLimit) {
        //Correct amount of riders selected
        if (m_SelectionCount == m_MaxSelections) {
            Exit(true);
        } else {
            //Incorrect amount of riders selected
            m_Logger->Log("You must select " + std::to_string(m_MaxSelections) + " options", Logger::LogLevelInfo, Logger::LogConsole);
            m_Logger->Log("User tried to save " + std::to_string(m_SelectionCount) + " selections, " + std::to_string(m_MaxSelections) + " required", Logger::LogLevelError, Logger::LogFile);
        }
        return;
    }

    //Shouldn't happen, but in that case will just close the menu, although its more likely that a segmentation error occurs
    if (m_SelectionCount > m_MaxSelections) {
        m_Logger->Log("More than the max amount of selections were selected, exiting", Logger::LogLevelError, Logger::LogConsoleFile);
        Exit(false);
        return;
    }

    //User tried to add more than six riders
    if (m_SelectionCount == m_MaxSelections) {
        m_Logger->Log("You have selected the max amount of selections", Logger::LogLevelInfo, Logger::LogConsole);
        return;
    }

    //User successfully selected a rider that isn't in the list yet
    if (CheckIfSelected(GetOptionIndex()) == -1) {
        int emptyIndex = GetEmptySpotSelections();
        //this shouldn't end up happening since we already checked if 6 riders are selected
        if (emptyIndex == -1) {
            m_Logger->Log("List is full while selectionCount says its not full, exiting", Logger::LogLevelError, Logger::LogFile);
            m_Logger->Log("There was an error in the selection menu, please try again", Logger::LogLevelError, Logger::LogConsole);
            Exit(false);
            return;
        }

        m_Selections[emptyIndex] = GetOptionIndex();
        gotoxy(GetRightArrow() + 5, GetHighlightedOption());

        std::cout << m_SelectionsCharacters[emptyIndex];
        m_SelectionCount++;

        m_Logger->Log("Selected option #" + std::to_string(GetOptionIndex()), Logger::LogLevelInfo, Logger::LogFile);

        return;
    }
}

void LimitedSelectionUi::OnDeselect() {
    int selected = CheckIfSelected(GetOptionIndex());
    if (selected == -1) {
        return;
    }

    m_Logger->Log("Removed selection #" + std::to_string(GetOptionIndex()), Logger::LogLevelInfo, Logger::LogFile);
    m_Selections[selected] = -1;
    gotoxy(GetRightArrow() + 5, GetHighlightedOption());
    std::cout << " ";
    m_SelectionCount--;
}
*/