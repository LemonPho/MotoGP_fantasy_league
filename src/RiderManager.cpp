#include "RiderManager.h"

RiderManager::RiderManager() {
    m_Rider = Rider();
    m_Points = 0;
    m_Position = 0;
}

void RiderManager::SetRider(Rider rider) {
    m_Rider = rider;
}

bool RiderManager::SetPoints(int points) {
    if(points < 0){
        return false;
    }

    m_Points = points;
    return true;
}

bool RiderManager::SetPosition(int position) {
    if(position < 0){
        return false;
    }

    m_Position = position;
    return true;
}

Rider &RiderManager::GetRider() {
    return m_Rider;
}

int RiderManager::GetPoints() {
    return m_Points;
}

int RiderManager::GetPosition() {
    return m_Position;
}

std::string RiderManager::ToString() {
    std::string result;
    std::string name = m_Rider.GetFirstName() + " " + m_Rider.GetLastName();

    result += util::FillSpaces(std::to_string(m_Position), Rider::SPACE_POSITION - std::to_string(m_Position).length());
    result += "|";
    result += util::FillSpaces(m_Rider.GetNumber(), Rider::SPACE_NUMBER - m_Rider.GetNumber().length());
    result += "|";
    result += util::FillSpaces(name, Rider::SPACE_NAME - name.length());
    result += "|";
    result += util::FillSpaces(std::to_string(m_Points), Rider::SPACE_POINTS - std::to_string(m_Points).length());
    result += "|";
    result += util::FillSpaces(m_Rider.GetCountry(), Rider::SPACE_COUNTRY - m_Rider.GetCountry().length());
    result += "|";
    result += util::FillSpaces(m_Rider.GetTeam(), Rider::SPACE_TEAM - m_Rider.GetTeam().length());
    result += "|";
    return result;
}

std::string RiderManager::ToStringIndexed(int index) {
    std::string result;
    std::string name = m_Rider.GetFirstName() + " " + m_Rider.GetLastName();

    result = std::to_string(index);
    result += " |";
    result += util::FillSpaces(name, Rider::SPACE_NAME - name.length());
    result += "|";
    result += util::FillSpaces(std::to_string(m_Points), Rider::SPACE_POINTS - std::to_string(m_Points).length());
    result += "|";
    result += util::FillSpaces(m_Rider.GetCountry(), Rider::SPACE_COUNTRY - m_Rider.GetCountry().length());
    result += "|";
    result += util::FillSpaces(m_Rider.GetTeam(), Rider::SPACE_TEAM - m_Rider.GetTeam().length());
    result += "|";

    return result;
}

std::string RiderManager::ToStringDisk() {
    std::string result;

    result += m_Rider.GetNumber();
    result += "|";
    result += m_Rider.GetFirstName();
    result += "|";
    result += m_Rider.GetLastName();
    result += "|";
    result += m_Rider.GetCountry();
    result += "|";
    result += m_Rider.GetTeam();
    result += "|";
    result += std::to_string(m_Points);
    result += "|";
    return result;
}

std::string RiderManager::ToStringSmall(bool spacing) {
    std::string result;

    result += m_Rider.GetFirstName()[0];
    result += ".";
    for(int i = 0; i < 3; i++){
        result += m_Rider.GetLastName()[i];
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

    result = m_Rider.GetFirstName();
    result += " ";
    result += m_Rider.GetLastName();

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
