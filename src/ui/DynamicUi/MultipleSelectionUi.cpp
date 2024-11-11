/*
#include "ui/DynamicUi/MultipleSelectionUi.h"

MultipleSelectionUi::MultipleSelectionUi(std::shared_ptr<Logger> logger, std::vector<std::string>& instructions, std::vector<std::string>& menuOptions) : DynamicUi(logger, instructions, menuOptions)
{
	m_Logger = logger;
	m_Selections.resize(menuOptions.size());
	for (auto& selection : m_Selections) {
		selection = false;
	}
}

std::vector<bool>& MultipleSelectionUi::GetSelections() {
	return m_Selections;
}

void MultipleSelectionUi::OnSelect(){
	size_t highlightedOption = GetHighlightedOption();
	std::vector<std::string> menuOptions = GetMenuOptions();
	size_t optionIndex = GetOptionIndex();
	size_t longestMenuOption = GetLongestMenuOption();

	if (highlightedOption == GetSelectionsSpace().lowerLimit) {
		Exit(true);
	} else {
		m_Logger->Log("Option: " + menuOptions[optionIndex] + " selected", Logger::LogLevelInfo, Logger::LogFile);
		int selectionPosition = (m_Window.columns / 2 + longestMenuOption / 2 + UiSpacing::SELECT_SPACING);
		gotoxy(selectionPosition, highlightedOption);
		std::cout << "x";
		m_Selections[optionIndex] = true;
	}
}

void MultipleSelectionUi::OnDeselect(){
	if (!m_Selections[GetOptionIndex()]) {
		return;
	}

	size_t highlightedOption = GetHighlightedOption();
	std::vector<std::string> menuOptions = GetMenuOptions();
	size_t optionIndex = GetOptionIndex();
	size_t longestMenuOption = GetLongestMenuOption();

	m_Logger->Log("Option: " + menuOptions[optionIndex] + " removed from selections", Logger::LogLevelInfo, Logger::LogFile);
	int selectionPosition = (m_Window.columns / 2 + longestMenuOption / 2 + UiSpacing::SELECT_SPACING);
	gotoxy(selectionPosition, highlightedOption);
	std::cout << " ";
	m_Selections[optionIndex] = false;
}
*/