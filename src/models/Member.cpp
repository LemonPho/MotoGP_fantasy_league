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
    m_Logger->Log("Rider " + riderManager.ToStringSmall(false) + " was added to " + m_UserName, Logger::LogLevelSuccess, Logger::LogFile);
}

void Member::SetRiderList(RiderManagerList riderList) {
    m_RiderList = riderList;
    m_Logger->Log("Rider list with " + std::to_string(riderList.GetRiderManagerList().size()) + " riders was added to " + m_UserName, Logger::LogLevelSuccess, Logger::LogFile);
}

bool Member::SetRiderManager(RiderManager riderManager, size_t index){
    if (index == Limits::RIDER_COUNT - 1) {
        return m_RiderList.SetRiderManager(riderManager, index, false);
    }

    size_t duplicates = 0;
    for (size_t i = 0; i < Limits::RIDER_COUNT - 2; i++) {
        if (m_RiderList.GetRiderManagerList()[i] == riderManager) {
            duplicates++;
        }
    }

    if (duplicates >= 1) {
        m_Logger->Log("Rider " + riderManager.ToStringSmall(false) + " already exists in " + m_UserName + "'s picks", Logger::LogLevelError, Logger::LogConsoleFile);
        return false;
    } else {
        return m_RiderList.SetRiderManager(riderManager, index, true);
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

float Member::GetPoints() {
    return m_Points;
}

std::string Member::ToStringSmall() {
    std::string result;
    std::ostringstream stream;
    

    result += m_UserName;
    result += " - ";
    stream << std::fixed << std::setprecision(0) << m_Points;
    result += stream.str();

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
