#pragma once

#include <iostream>
#include <vector>

#include "core/Logger.h"	
#include "ui/DynamicUi/Window.h"

class BaseUiElement {
public:
	enum Padding {
		PADDING_X = 2,
		PADDING_Y = 1,
	};

	enum class Positioning {
		LEFT=0,
		CENTERED,
		RIGHT,
	};

	enum class SelectionType {
		SINGLE = 0,
		MULTIPLE,
		NO_SELECTIONS,
		WRONG_USAGE,
	};

	struct Size {
		size_t height;
		size_t width;
	};

	struct Coordinate {
		size_t y;
		size_t x;
	};

	struct Coordinates {
		Coordinate topLeftCoordinate;
		Coordinate topRightCoordinate;
		Coordinate bottomLeftCoordinate;
		Coordinate bottomRightCoordinate;
	};
	
private:
	std::shared_ptr<Logger> m_Logger;

	//label used to refer to the element
	std::string m_Label = "";

	//positioning, size
	Size m_Size;
	Positioning m_Positioning;
	Coordinates m_Coordinates;
	std::vector<std::string> m_ContentArray;

	//ui element is disabled if its too wide for screen
	bool m_Disabled = false;
protected:
	Window m_Window;
	void gotoxy(size_t y, size_t x);

public:
	BaseUiElement(std::shared_ptr<Logger> logger, std::string label, Positioning positioning, std::vector<std::string> contentArray);

	virtual void InitializeUiElement(Window window, size_t y);


	Size GetSize();
	Coordinates GetCoordinates();
	Positioning GetPositioning();

	void Display();
	void Disable();

	virtual void IncreaseSelection();
	virtual void DecreaseSelection();

	virtual int GetSelection();
	virtual std::vector<int>& GetSelections();
	virtual SelectionType GetSelectionType();

	virtual void OnKeyUp();
	virtual void OnKeyDown();
	virtual void OnSelect();
	virtual void OnDeselect();
};