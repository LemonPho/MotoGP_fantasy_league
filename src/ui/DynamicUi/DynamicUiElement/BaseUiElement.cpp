#include "ui/DynamicUi/DynamicUiElement/BaseUiElement.h"

void BaseUiElement::gotoxy(size_t y, size_t x) {
	std::cout << "\033[" << y << ";" << x << "H";
}

BaseUiElement::BaseUiElement(std::shared_ptr<Logger> logger, std::string label, Positioning positioning, std::vector<std::string> contentArray) :
	m_Logger(logger), m_Positioning(positioning), m_Label(label), m_ContentArray(contentArray) {

	m_Logger->Log("Initializing " + label + " ui element", Logger::LogLevelInfo, Logger::LogFile);

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
		m_Coordinates.topLeftCoordinate.x = 0;
		m_Coordinates.topLeftCoordinate.y = y;
		m_Coordinates.topRightCoordinate.x = m_Size.width + 1;
		m_Coordinates.topRightCoordinate.y = y;
		m_Coordinates.bottomLeftCoordinate.x = 0;
		m_Coordinates.bottomLeftCoordinate.y = m_Size.height + y + 1;
		m_Coordinates.bottomRightCoordinate.x = m_Size.width + 1;
		m_Coordinates.bottomRightCoordinate.y = y + m_Size.height + 1;
	} else if (m_Positioning == Positioning::CENTERED) {
		m_Coordinates.topLeftCoordinate.x = (m_Window.columns / 2) - (m_Size.width / 2);
		m_Coordinates.topLeftCoordinate.y = y;
		m_Coordinates.topRightCoordinate.x = (m_Window.columns / 2 + 1) + (m_Size.width / 2) + 1;
		m_Coordinates.topRightCoordinate.y = y;
		m_Coordinates.bottomLeftCoordinate.x = (m_Window.columns / 2) - (m_Size.width / 2);
		m_Coordinates.bottomLeftCoordinate.y = m_Size.height + y + 1;
		m_Coordinates.bottomRightCoordinate.x = (m_Window.columns / 2 + 1) + (m_Size.width / 2) + 1;
		m_Coordinates.bottomRightCoordinate.y = y + m_Size.height + 1;

		//push border one more space if the width is impar
		if (m_Size.width % 2 != 0) {
			m_Coordinates.topRightCoordinate.x++;
			m_Coordinates.bottomRightCoordinate.x++;
		}
	} else if (m_Positioning == Positioning::RIGHT) {
		m_Coordinates.topLeftCoordinate.x = m_Window.columns - m_Size.width - 2;
		m_Coordinates.topLeftCoordinate.y = y;
		m_Coordinates.topRightCoordinate.x = m_Window.columns - 1;
		m_Coordinates.topRightCoordinate.y = y;
		m_Coordinates.bottomLeftCoordinate.x = m_Window.columns - m_Size.width - 2;
		m_Coordinates.bottomLeftCoordinate.y = m_Size.height + y + 1;
		m_Coordinates.bottomRightCoordinate.x = m_Window.columns - 1;
		m_Coordinates.bottomRightCoordinate.y = y + m_Size.height + 1;
	}
	m_Logger->Log("Initialized " + m_Label + " ui element", Logger::LogLevelInfo, Logger::LogFile);
}

void BaseUiElement::Disable() {
	m_Logger->Log("Disabled " + m_Label + " ui, try putting the application in full screen before opening this menu", Logger::LogLevelWarning, Logger::LogConsole);
	m_Disabled = true;
}

BaseUiElement::Size BaseUiElement::GetSize() {
	return m_Size;
}

BaseUiElement::Coordinates BaseUiElement::GetCoordinates() {
	return m_Coordinates;
}

BaseUiElement::Positioning BaseUiElement::GetPositioning() {
	return m_Positioning;
}

void BaseUiElement::Display() {
	if (m_Disabled) {
		return;
	}

	m_Logger->Log("Displaying " + m_Label + " ui", Logger::LogLevelInfo, Logger::LogFile);
	for (int i = 0; i < m_ContentArray.size(); i++) {
		if (m_Positioning == Positioning::LEFT) {
			gotoxy(i + m_Coordinates.topLeftCoordinate.y + Padding::PADDING_Y, m_Coordinates.topLeftCoordinate.x + Padding::PADDING_X);
		} else if (m_Positioning == Positioning::CENTERED) {
			gotoxy(i + m_Coordinates.topLeftCoordinate.y + Padding::PADDING_Y, (m_Window.columns / 2) - (m_ContentArray[i].length()/2) + Padding::PADDING_X);
		} else if (m_Positioning == Positioning::RIGHT) {
			gotoxy(i + m_Coordinates.topLeftCoordinate.y + Padding::PADDING_Y, m_Window.columns - m_ContentArray[i].length() - Padding::PADDING_X);
		}

		std::cout << m_ContentArray[i];
	}
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

BaseUiElement::SelectionType BaseUiElement::GetSelectionType() {
	return SelectionType::NO_SELECTIONS;
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
