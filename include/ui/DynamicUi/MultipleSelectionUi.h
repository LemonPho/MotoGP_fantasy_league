/*
#ifndef MOTOGP_FANTASY_LEAGUE_MODERN_MULTIPLESELECTIONUI_H
#define MOTOGP_FANTASY_LEAGUE_MDOERN_MULTIPLESELECITONUI_H

#include "DynamicUi.h"
#include "core/Logger.h"

class MultipleSelectionUi : public DynamicUi {
private:
	std::shared_ptr<Logger> m_Logger;
	std::vector<bool> m_Selections;
public:
	MultipleSelectionUi(std::shared_ptr<Logger> logger, std::vector<std::string>& instructions, std::vector<std::string>& menuOptions);

	std::vector<bool>& GetSelections();

	void OnSelect() override;
	void OnDeselect() override;
};

#endif */