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

	enum class ReturnType {
		SINGLE_SELECTION = 0,
		MULTIPLE_SELECTIONS,
		STRING,
		NO_RETURN,
	};

	struct Size {
		size_t height;
		size_t width;
	};

	struct Coordinates {
		size_t left = 0;
		size_t top = 0;
		size_t right = 0;
		size_t bottom = 0;
	};
	
private:
	std::shared_ptr<Logger> m_Logger;
	std::shared_ptr<bool> m_Terminate = nullptr;

	//label used to refer to the element
	std::string m_Label = "";

	//positioning, size
	Size m_Size;
	Positioning m_Positioning;
	Coordinates m_Coordinates;
	std::vector<std::string> m_ContentArray;

	ReturnType m_ReturnType = ReturnType::NO_RETURN;

	//ui element is disabled if its too wide for screen
	bool m_Disabled = false;
	bool m_Static = true;
	bool m_ChangesMade = false;
protected:
	Window m_Window;
	void gotoxy(size_t y, size_t x);

public:
	BaseUiElement(std::shared_ptr<Logger> logger, std::string label, Positioning positioning, const std::vector<std::string>& contentArray);

	virtual void InitializeUiElement(Window window, size_t y);

	virtual void SetTerminate(std::shared_ptr<bool> terminate);
	void SetStatic(bool isStatic);
	void SetChangesMade(bool changesMade);
	void SetCoordinates(Coordinates coordinates);
	void SetPositioning(Positioning positioning);
	
	const Size GetSize();
	const Coordinates GetCoordinates();
	const Positioning GetPositioning();
	const bool GetStatic();
	const bool GetDisabled();
	const std::string GetLabel();
	std::vector<std::string>& GetContentArray();

	void Display();
	void PrintString(std::string& string, size_t y);
	void Disable();

	virtual void IncreaseSelection();
	virtual void DecreaseSelection();

	virtual int GetSelection();
	virtual std::vector<int>& GetSelections();
	virtual std::string& GetInput();
	bool GetChangesMade();
	virtual ReturnType GetReturnType();

	virtual void OnKeyUp();
	virtual void OnKeyDown();
	virtual void OnSelect();
	virtual void OnDeselect();
	void Exit();
};