#include "RiderManager.h"

RiderManager::RiderManager() {
    m_Rider = std::make_shared<Rider>();
    m_Logger = nullptr;
    m_Points = 0;
    m_Position = 0;
}

RiderManager::RiderManager(std::shared_ptr<Logger> logger) {
    m_Logger = logger;
    m_Rider = std::make_shared<Rider>();
    m_Points = 0;
    m_Position = 0;
}

RiderManager::RiderManager(std::shared_ptr<Rider> rider, std::shared_ptr<Logger> logger){
    m_Rider = rider;
    m_Logger = logger;
}

void RiderManager::SetLogger(std::shared_ptr<Logger> logger) {
    m_Logger = logger;
}

void RiderManager::SetRider(std::shared_ptr<Rider> rider) {
    m_Rider = rider;
}

bool RiderManager::SetPoints(int points) {
    if(points < 0){
        m_Logger->Log("Tried to set points to " + std::to_string(points) + " on rider with number: " + this->m_Rider->GetNumber(), Logger::LogLevelError, Logger::LogConsoleFile);
        return false;
    }

    m_Points = points;
    return true;
}

bool RiderManager::SetPosition(int position) {
    if(position < 0){
        m_Logger->Log("Tried to set position to " + std::to_string(position) + " on rider with number: " + this->m_Rider->GetNumber(), Logger::LogLevelError, Logger::LogConsoleFile);
        return false;
    }

    m_Position = position;
    return true;
}

Rider &RiderManager::GetRider() {
    return *m_Rider;
}

int RiderManager::GetPoints() {
    return m_Points;
}

int RiderManager::GetPosition() {
    return m_Position;
}

std::string RiderManager::ToString() {
    std::string result;
    std::string name = m_Rider->GetFirstName() + " " + m_Rider->GetLastName();

    result += util::FillSpaces(std::to_string(m_Position), Rider::SPACE_POSITION - std::to_string(m_Position).length());
    result += "|";
    result += util::FillSpaces(m_Rider->GetNumber(), Rider::SPACE_NUMBER - m_Rider->GetNumber().length());
    result += "|";
    result += util::FillSpaces(name, Rider::SPACE_NAME - name.length());
    result += "|";
    result += util::FillSpaces(std::to_string(m_Points), Rider::SPACE_POINTS - std::to_string(m_Points).length());
    result += "|";
    result += util::FillSpaces(m_Rider->GetCountry(), Rider::SPACE_COUNTRY - m_Rider->GetCountry().length());
    result += "|";
    result += util::FillSpaces(m_Rider->GetTeam(), Rider::SPACE_TEAM - m_Rider->GetTeam().length());
    result += "|";
    return result;
}

std::string RiderManager::ToStringIndexed(int index) {
    std::string result;
    std::string name = m_Rider->GetFirstName() + " " + m_Rider->GetLastName();

    result = std::to_string(index);
    result += " |";
    result += util::FillSpaces(name, Rider::SPACE_NAME - name.length());
    result += "|";
    result += util::FillSpaces(std::to_string(m_Points), Rider::SPACE_POINTS - std::to_string(m_Points).length());
    result += "|";
    result += util::FillSpaces(m_Rider->GetCountry(), Rider::SPACE_COUNTRY - m_Rider->GetCountry().length());
    result += "|";
    result += util::FillSpaces(m_Rider->GetTeam(), Rider::SPACE_TEAM - m_Rider->GetTeam().length());
    result += "|";

    return result;
}

std::string RiderManager::ToStringDisk() {
    std::string result;

    result += m_Rider->GetNumber();
    result += "|";
    result += m_Rider->GetFirstName();
    result += "|";
    result += m_Rider->GetLastName();
    result += "|";
    result += m_Rider->GetCountry();
    result += "|";
    result += m_Rider->GetTeam();
    result += "|";
    result += std::to_string(m_Points);
    result += "|";
    return result;
}

std::string RiderManager::ToStringSmall(bool spacing) {
    std::string result;

    result += m_Rider->GetFirstName()[0];
    result += ".";
    for(int i = 0; i < 3; i++){
        result += m_Rider->GetLastName()[i];
    }
    result += " - ";
    result += std::to_string(m_Points);

    if(spacing) {
        result = util::FillSpaces(result, Rider::SPACE_PRINT_SMALL - result.length());
    }

    return result;
}

std::string RiderManager::ToStringSmallFullName() {
    std::string result;

    result = m_Rider->GetFirstName();
    result += " ";
    result += m_Rider->GetLastName();

    return result;
}

RiderManager &RiderManager::operator=(const RiderManager &riderManager) {
    m_Rider = riderManager.m_Rider;
    m_Points = riderManager.m_Points;
    m_Position = riderManager.m_Position;

    return *this;
}

bool RiderManager::operator==(const RiderManager &riderManager) {
    return this->m_Rider == riderManager.m_Rider;
}

bool RiderManager::operator>=(const RiderManager &riderManager) {
    return this->m_Rider >= riderManager.m_Rider;
}

bool RiderManager::operator!=(const RiderManager &riderManager) {
    return this->m_Rider != riderManager.m_Rider;
}

bool RiderManager::operator<=(const RiderManager &riderManager) {
    return this->m_Rider <= riderManager.m_Rider;
}

bool RiderManager::operator<(const RiderManager &riderManager) {
    return this->m_Rider < riderManager.m_Rider;
}

bool RiderManager::operator>(const RiderManager &riderManager) {
    return this->m_Rider > riderManager.m_Rider;
}
