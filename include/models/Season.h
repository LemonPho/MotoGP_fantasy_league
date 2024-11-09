#pragma once

#include <iostream>

#include "core/Logger.h"
#include "views/MemberList.h"
#include "views/RiderManagerList.h"

class Season {
private:
	std::shared_ptr<Logger> m_Logger;
	std::string m_SeasonName;
	MemberList m_MemberList;
	RiderManagerList m_RiderManagerList;

public:
	Season();
	void InitializeSeason(std::shared_ptr<Logger> logger, std::string seasonName);

	MemberList GetMemberList();
	RiderManagerList GetRiderManagerList();
	std::string GetSeasonName();

	void SetMemberList(MemberList memberList);
	void SetRiderManagerList(RiderManagerList riderManagerList);

	void SaveChanges();
	void LoadFromDisk();
};