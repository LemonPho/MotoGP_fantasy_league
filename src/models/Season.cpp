#include "models/Season.h"

Season::Season() {
	m_Logger = std::make_shared<Logger>();
	m_SeasonName = "";
}

void Season::InitializeSeason(std::shared_ptr<Logger> logger, std::string seasonName, bool finalized) {
	m_Logger->Log("Initializing season with season name: " + seasonName, Logger::LogLevelInfo, Logger::LogFile);
	m_Logger = logger;
	m_MemberList = MemberList(logger);
	m_RiderManagerList = RiderManagerList(logger);
	m_SeasonName = seasonName;
	m_Finalized = finalized;
	LoadFromDisk();
	m_Logger->Log("Season initialized", Logger::LogLevelSuccess, Logger::LogFile);
}

void Season::FinalizeSeason() {
	m_Finalized = true;

}

void Season::SortMembers() {
	if (!m_Finalized) {
		m_MemberList.UpdateMembersPoints();
	} else {
		m_MemberList.AddFinalizedPoints(m_RiderManagerList);
	}
	m_MemberList.SortMembers(false);
}

bool Season::GetFinalized() {
	return m_Finalized;
}

MemberList& Season::GetMemberList() {
	return m_MemberList;
}

RiderManagerList& Season::GetRiderManagerList() {
	return m_RiderManagerList;
}

std::string Season::GetSeasonName() {
	return m_SeasonName;
}

void Season::SetMemberList(MemberList memberList) {
	m_MemberList = memberList;
}

void Season::SetRiderManagerList(RiderManagerList riderManagerList) {
	m_RiderManagerList = riderManagerList;
}

void Season::SaveChanges() {
	m_RiderManagerList.WriteToDisk(util::APP_DIRECTORY_DATA / (m_SeasonName + util::RIDER_DATA));
	m_MemberList.WriteToDisk(util::APP_DIRECTORY_DATA / (m_SeasonName + util::MEMBER_DATA));
}

void Season::LoadFromDisk() {
	m_RiderManagerList.ReadFromDisk(util::APP_DIRECTORY_DATA / (m_SeasonName + util::RIDER_DATA));
	m_MemberList.ReadFromDisk(util::APP_DIRECTORY_DATA / (m_SeasonName + util::MEMBER_DATA), m_RiderManagerList);
}
