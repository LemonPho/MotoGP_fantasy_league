#include "ui/DynamicUi/DynamicUiElement/BaseUiElement.h"

void BaseUiElement::gotoxy(size_t y, size_t x) {
	std::cout << "\033[" << y << ";" << x << "H";
}

BaseUiElement::BaseUiElement(std::shared_ptr<Logger> logger, std::string label, Positioning positioning, const std::vector<std::string>& contentArray) :
	m_Logger(logger), m_Positioning(positioning), m_Label(label), m_ContentArray(contentArray) {

	m_Logger->Log("Initializing " + label + " ui element", Logger::LogLevelInfo, Logger::LogFile);

	m_Coordinates.left = 0;
	m_Coordinates.top = 0;
	m_Coordinates.right = 0;
	m_Coordinates.bottom = 0;
	m_Window.rows = 0;
	m_Window.columns = 0;

	size_t longestContentString = 0;

	for (auto& contentString : contentArray) {
		if (contentString.length() > longestContentString) {
			longestContentString = contentString.length();
		}
	}
	
	m_Size.height = contentArray.size();
	m_Size.width = longestContentString;

	m_Logger->Log("Initialized " + label + " ui element", Logger::LogLevelInfo, Logger::LogFile);
}

void BaseUiElement::InitializeUiElement(Window window, size_t y) {
	m_Logger->Log("Initializing " + m_Label + " ui element", Logger::LogLevelInfo, Logger::LogFile);
	m_Window = window;
	if (m_Size.width > m_Window.columns) {
		m_Logger->Log("ui element " + m_Label + " is too wide for the screen", Logger::LogLevelWarning, Logger::LogFile);
		Disable();
		return;
	}

	if (m_Positioning == Positioning::LEFT) {
		m_Coordinates.left = 0;
		m_Coordinates.top = y;
		m_Coordinates.right = m_Size.width + Padding::PADDING_X;
		m_Coordinates.bottom = m_Size.height + y + Padding::PADDING_Y;
	} else if (m_Positioning == Positioning::CENTERED) {
		m_Coordinates.left = (m_Window.columns / 2) - (m_Size.width / 2);
		m_Coordinates.top = y;
		m_Coordinates.right = (m_Window.columns / 2 + 1) + (m_Size.width / 2) + Padding::PADDING_X;
		m_Coordinates.bottom = m_Size.height + y + Padding::PADDING_Y;

		//push border one more space if the width is even
		if (m_Size.width % 2 == 0) {
			m_Coordinates.right++;
		}
	} else if (m_Positioning == Positioning::RIGHT) {
		m_Coordinates.left = m_Window.columns - m_Size.width - 2;
		m_Coordinates.top = y;
		m_Coordinates.right = m_Window.columns - 1 + Padding::PADDING_X;
		m_Coordinates.bottom = m_Size.height + y + Padding::PADDING_Y;
	}
	m_Logger->Log("Initialized " + m_Label + " ui element", Logger::LogLevelInfo, Logger::LogFile);
}

void BaseUiElement::SetTerminate(std::shared_ptr<bool> terminate) {
	m_Terminate = terminate;
}

void BaseUiElement::SetStatic(bool isStatic) {
	m_Static = isStatic;
}

void BaseUiElement::SetChangesMade(bool changesMade) {
	m_ChangesMade = changesMade;
}

void BaseUiElement::SetCoordinates(Coordinates coordinates) {
	m_Coordinates = coordinates;
}

void BaseUiElement::SetPositioning(Positioning positioning) {
	m_Positioning = positioning;
}

void BaseUiElement::Disable() {
	m_Logger->Log("Disabled " + m_Label + " ui, try putting the application in full screen before opening this menu", Logger::LogLevelWarning, Logger::LogConsole);
	m_Disabled = true;
}

const BaseUiElement::Size BaseUiElement::GetSize() {
	return m_Size;
}

const BaseUiElement::Coordinates BaseUiElement::GetCoordinates() {
	return m_Coordinates;
}

const BaseUiElement::Positioning BaseUiElement::GetPositioning() {
	return m_Positioning;
}

const bool BaseUiElement::GetStatic() {
	return m_Static;
}

const bool BaseUiElement::GetDisabled() {
	return m_Disabled;
}

const std::string BaseUiElement::GetLabel() {
	return m_Label;
}

std::vector<std::string>& BaseUiElement::GetContentArray() {
	return m_ContentArray;
}

void BaseUiElement::Display() {
	if (m_Disabled) {
		return;
	}

	m_Logger->Log("Displaying " + m_Label + " ui", Logger::LogLevelInfo, Logger::LogFile);
	for (int i = 0; i < m_ContentArray.size(); i++) {
		PrintString(m_ContentArray[i], i);
	}
}

void BaseUiElement::PrintString(std::string& string, size_t y) {
	if (m_Positioning == Positioning::LEFT) {
		gotoxy(y + m_Coordinates.top + Padding::PADDING_Y, m_Coordinates.left + Padding::PADDING_X);
	} else if (m_Positioning == Positioning::CENTERED) {
		gotoxy(y + m_Coordinates.top + Padding::PADDING_Y, (m_Window.columns / 2) - (string.length() / 2) + Padding::PADDING_X);
	} else if (m_Positioning == Positioning::RIGHT) {
		gotoxy(y + m_Coordinates.top + Padding::PADDING_Y, m_Window.columns - string.length() - Padding::PADDING_X);
	}

	std::cout << string;
}

void BaseUiElement::IncreaseSelection() {
	return;
}

void BaseUiElement::DecreaseSelection() {
	return;
}

int BaseUiElement::GetSelection() {
	return 0;
}

std::vector<int>& BaseUiElement::GetSelections() {
	return std::vector<int>();
}

std::string& BaseUiElement::GetInput() {
	std::string string = "";
	return string;
}

bool BaseUiElement::GetChangesMade() {
	return m_ChangesMade;
}

BaseUiElement::ReturnType BaseUiElement::GetReturnType() {
	return ReturnType::NO_RETURN;
}

void BaseUiElement::OnKeyUp() {
	return;
}

void BaseUiElement::OnKeyDown() {
	return;
}

void BaseUiElement::OnSelect() {
	return;
}

void BaseUiElement::OnDeselect() {
	return;
}

void BaseUiElement::Exit() {
	*m_Terminate = true;
}
