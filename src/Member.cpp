#include "Member.h"

Member::Member() {
    m_UserName = "";
    m_Points = 0;
    m_Logger = std::make_shared<Logger>();
}

Member::Member(std::shared_ptr<Logger> logger){
    m_Logger = logger;
}

bool Member::SetUserName(const std::string &userName) {
    if(userName.length() > MAX_USERNAME){
        m_Logger->Log("Username can't be more than " + std::to_string(MAX_USERNAME) + " characters", Logger::LogLevelError,Logger::LogConsoleFile);
        return false;
    }

    m_UserName = userName;

    return true;
}

void Member::InsertRiderManager(RiderManager &riderManager) {
    m_RiderList.push_back(riderManager);
    m_Logger->Log("Rider with number: " + riderManager.GetRider().GetNumber() + " was added to " + m_UserName, Logger::LogLevelSuccess, Logger::LogFile);
}

void Member::SetRiderList(std::vector<RiderManager> riderList) {
    m_RiderList = riderList;
    m_Logger->Log("Rider list with " + std::to_string(riderList.size()) + " riders was added to " + m_UserName, Logger::LogLevelSuccess, Logger::LogFile);
}

bool Member::SetPoints(int points) {
    if(points < 0){
        m_Logger->Log("Tried to set " + this->m_UserName + " points to " + std::to_string(points), Logger::LogLevelError, Logger::LogConsoleFile);
        return false;
    }

    m_Points = points;
    return true;
}

std::string Member::GetUserName() {
    return m_UserName;
}

std::vector<RiderManager> Member::GetRiderList() {
    return m_RiderList;
}

int Member::GetPoints() {
    return m_Points;
}

std::string Member::ToStringSmall() {
    std::string result;

    result += m_UserName;
    result += " - ";
    result += std::to_string(m_Points);

    result = util::FillSpaces(result, SPACE_USERNAME - result.length());

    for(auto rider: m_RiderList){
        result += rider.ToStringSmall(true);
        result += " ";
    }

    return result;
}

Member& Member::operator=(const Member &member) {
    m_UserName = member.m_UserName;
    m_Logger = member.m_Logger;
    m_Points = member.m_Points;
    return *this;
}

bool Member::operator==(const Member &member) {
    return m_UserName == member.m_UserName;
}

bool Member::operator < (const Member &member) {
    return m_Points < member.m_Points;
}
