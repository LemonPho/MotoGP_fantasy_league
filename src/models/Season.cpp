#include "models/Season.h"

Season::Season() {
	m_Logger = std::make_shared<Logger>();
	m_SeasonName = "";
}

void Season::InitializeSeason(std::shared_ptr<Logger> logger, std::string seasonName) {
	m_Logger->Log("Initializing season with season name: " + seasonName, Logger::LogLevelInfo, Logger::LogFile);
	m_Logger = logger;
	m_MemberList = MemberList(logger);
	m_RiderManagerList = RiderManagerList(logger);
	m_SeasonName = seasonName;
	LoadFromDisk();
	m_Logger->Log("Season initialized", Logger::LogLevelSuccess, Logger::LogFile);
}

MemberList Season::GetMemberList() {
	return m_MemberList;
}

RiderManagerList Season::GetRiderManagerList() {
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
