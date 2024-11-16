#include "ui/DynamicUi/DynamicUiElement/SingleSelectionUiElement.h"

SingleSelectionUiElement::SingleSelectionUiElement(std::shared_ptr<Logger> logger, const std::string label, Positioning positioning, const std::vector<std::string>& contentArray) : BaseUiElement(logger, label, positioning, contentArray) {
	m_Logger = logger;
	SetStatic(false);
}

void SingleSelectionUiElement::InitializeUiElement(Window window, size_t y) {
	m_Logger->Log("Initializing " + GetLabel() + " ui element", Logger::LogLevelInfo, Logger::LogFile);
	m_Window = window;
	if (GetSize().width > m_Window.columns) {
		m_Logger->Log("ui element " + GetLabel() + " is too wide for the screen", Logger::LogLevelWarning, Logger::LogFile);
		Disable();
		return;
	}

	Coordinates tempCoordinates;

	if (GetPositioning() == Positioning::LEFT) {
		tempCoordinates.left = 0;
		tempCoordinates.top = y;
		tempCoordinates.right = GetSize().width + Padding::PADDING_X;
		tempCoordinates.bottom = GetSize().height + y + Padding::PADDING_Y;
	} else if (GetPositioning() == Positioning::CENTERED) {
		tempCoordinates.left = (m_Window.columns / 2) - (GetSize().width / 2);
		tempCoordinates.top = y;
		tempCoordinates.right = (m_Window.columns / 2 + 1) + (GetSize().width / 2) + Padding::PADDING_X;
		tempCoordinates.bottom = GetSize().height + y + Padding::PADDING_Y;

		//push border one more space if the width is even
		if (GetSize().width % 2 == 0) {
			tempCoordinates.right++;
		}
	} else if (GetPositioning() == Positioning::RIGHT) {
		tempCoordinates.left = m_Window.columns - GetSize().width - 2;
		tempCoordinates.top = y;
		tempCoordinates.right = m_Window.columns - 1 + Padding::PADDING_X;
		tempCoordinates.bottom = GetSize().height + y + Padding::PADDING_Y;
	}

	SetCoordinates(tempCoordinates);

	m_Logger->Log("Initialized " + GetLabel() + " ui element", Logger::LogLevelInfo, Logger::LogFile);
}

int SingleSelectionUiElement::GetSelection() {
	return m_Selection;
}

void SingleSelectionUiElement::RemoveHightlight(std::string& string, size_t y) {
	std::cout << "\033[0m";
	PrintString(string, y);
}

void SingleSelectionUiElement::PrintHightlight(std::string& string, size_t y) {
	std::cout << "\033[0;46m";
	PrintString(string, y);
	std::cout << "\033[0m";
}

void SingleSelectionUiElement::OnKeyUp() {
	std::vector<std::string>& tempContentArray = GetContentArray();
	RemoveHightlight(tempContentArray[m_OptionIndex], m_OptionIndex);
	if (m_OptionIndex == 0) {
		m_OptionIndex = tempContentArray.size() - Padding::PADDING_Y;
	} else {
		m_OptionIndex--;
	}
	PrintHightlight(tempContentArray[m_OptionIndex], m_OptionIndex);
}

void SingleSelectionUiElement::OnKeyDown() {
	std::vector<std::string>& tempContentArray = GetContentArray();
	RemoveHightlight(tempContentArray[m_OptionIndex], m_OptionIndex);
	m_OptionIndex++;
	m_OptionIndex %= GetContentArray().size();
	PrintHightlight(tempContentArray[m_OptionIndex], m_OptionIndex);
}

void SingleSelectionUiElement::OnSelect() {
	m_Selection = m_OptionIndex;
	SetChangesMade(true);
	Exit();
}
