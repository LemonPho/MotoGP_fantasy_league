#include "models/Member.h"

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
    m_RiderList.AddRiderManager(riderManager);
    m_Logger->Log("Rider with number: " + riderManager.GetRider().GetNumber() + " was added to " + m_UserName, Logger::LogLevelSuccess, Logger::LogFile);
}

void Member::SetRiderList(RiderManagerList riderList) {
    m_RiderList = riderList;
    m_Logger->Log("Rider list with " + std::to_string(riderList.GetRiderManagerList().size()) + " riders was added to " + m_UserName, Logger::LogLevelSuccess, Logger::LogFile);
}

bool Member::SetRiderManager(RiderManager riderManager, size_t index){
    size_t duplicates = 0;
    for (size_t i = 0; i < Limits::RIDER_COUNT - 2; i++) {
        if (m_RiderList.GetRiderManagerList()[i] == riderManager) {
            duplicates++;
        }
    }

    if (duplicates >= 1) {
        m_Logger->Log("Rider #" + riderManager.GetRider().GetNumber() + " already exists in " + m_UserName + "'s picks", Logger::LogLevelError, Logger::LogConsoleFile);
        return false;
    } else {
        return m_RiderList.SetRiderManager(riderManager, index);
    }
}

bool Member::SetPoints(int points) {
    if(points < 0){
        m_Logger->Log("Tried to set " + this->m_UserName + " points to " + std::to_string(points), Logger::LogLevelError, Logger::LogConsoleFile);
        return false;
    }

    m_Points = points;
    return true;
}

std::string Member::GetMemberUserName() {
    return m_UserName;
}

RiderManagerList Member::GetRiderList() {
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

    result = util::FillSpaces(result, Spacing::USERNAME_SPACING - result.length());

    result += m_RiderList.ToStringSmall(true);

    return result;
}

std::vector<std::string> Member::ToStringEdit() {
    std::vector<std::string> result(2);

    result[0] = "Username: " + m_UserName;
    result[1] = "User picks: " + m_RiderList.ToStringSmall(false);

    return result;
}

Member& Member::operator=(const Member &member) {
    m_UserName = member.m_UserName;
    m_Logger = member.m_Logger;
    m_Points = member.m_Points;
    m_RiderList = member.m_RiderList;
    return *this;
}

bool Member::operator==(const Member &member) {
    return m_UserName == member.m_UserName;
}

bool Member::operator < (const Member &member) {
    return m_Points < member.m_Points;
}
