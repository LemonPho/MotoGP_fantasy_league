#ifndef MOTOGP_FANTASY_LEAGUE_MODERN_MEMBERSELECTORUI_H
#define MOTOGP_FANTASY_LEAGUE_MODERN_MEMBERSELECTORUI_H

#include "ui/DynamicUi/DynamicUi.h"
#include "core/Logger.h"

class MemberSelectorUi : public DynamicUi {
private:
	size_t m_Selections = 0;
	std::shared_ptr<Logger> m_Logger;
public:
	MemberSelectorUi(std::shared_ptr<Logger> logger, std::vector<std::string>& instructions, std::vector<std::string>& menuOptions);

	size_t GetSelections();
	
	void OnSelect() override;
	void OnDeselect() override;

	~MemberSelectorUi() override = default;
};

#endif