#ifndef MOTOGP_FANTASY_LEAGUE_MODERN_LIMITEDSELECTIONUI_H
#define MOTOGP_FANTASY_LEAGUE_MODERN_LIMITEDSELECTIONUI_H

#include "DynamicUi.h"

class LimitedSelectionUi : public DynamicUi {
public:
	enum LimitedSelectionUiSpacing {
		MESSAGE_LINE_SPACING = 1,
	};
private:
	std::shared_ptr<Logger> m_Logger;
	std::vector<std::string> m_SelectionsCharacters;
	std::vector<int> m_Selections;
	size_t m_MaxSelections = 0;
	size_t m_SelectionCount = 0;

	int CheckIfSelected(size_t query);
	int GetEmptySpotSelections();
public:
	LimitedSelectionUi(std::shared_ptr<Logger> logger, std::vector<std::string>& instructions, std::vector<std::string>& menuOptions, std::vector<std::string>& selectionsCharacters);

	std::vector<int> GetSelections();

	void OnSelect() override;
	void OnDeselect() override;
};

#endif