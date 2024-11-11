#pragma once

#include <iostream>
#include <vector>

#include "ui/DynamicUi/DynamicUi.h"

class BaseUiElement {
public:
	enum class Positioning {
		LEFT=0,
		CENTERED,
		RIGHT,
	};

	enum class SelectionType {
		SINGLE = 0,
		MULTIPLE,
		WRONG_USAGE,
	};

	struct Size {
		size_t height;
		size_t width;
	};

	struct Coordinate {
		size_t x;
		size_t y;
	};
	
private:
	std::shared_ptr<Logger> m_Logger;

	//label used to refer to the element
	std::string m_Label = "";

	//positioning, size
	Size m_Size;
	Coordinate m_Coordinates;
	Positioning m_Positioning;

	std::vector<std::string> m_ContentArray;
public:
	BaseUiElement(std::shared_ptr<Logger> logger, std::string label, Positioning positioning, std::vector<std::string> contentArray);

	Size GetSize();
	Coordinate GetCoordinates();
	Positioning GetPositioning();

	virtual int GetSelection();
	virtual std::vector<int>& GetSelections();
	virtual SelectionType GetSelectionType();

	virtual void OnSelect();
	virtual void OnDeselect();
};