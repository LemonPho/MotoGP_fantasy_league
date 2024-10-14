#include "Rider.h"

Rider::Rider() {
    m_Logger = std::make_shared<Logger>();
    m_FirstName = "First name";
    m_LastName = "Last name";
    m_Number = "0";
    m_Country = "Country";
    m_Team = "Team";
}

Rider::Rider(std::shared_ptr<Logger> logger) {
    m_Logger = logger;
    m_FirstName = "First name";
    m_LastName = "Last name";
    m_Number = "0";
    m_Country = "Country";
    m_Team = "Team";
}

bool Rider::SetData(const std::string &firstName, const std::string &lastName, const std::string &number, const std::string &country, const std::string &team) {
    if(std::stoi(number) < 1 || std::stoi(number) > 99){
        m_Logger->Log("Invalid number: " + number, Logger::LogLevelError, Logger::LogConsoleFile);
        return false;
    }

    m_FirstName = firstName;
    m_LastName = lastName;
    m_Number = number;
    m_Country = country;
    m_Team = team;

    return true;
}

bool Rider::SetNumber(const std::string &number) {
    if(std::stoi(number) < 1 || std::stoi(number) > 99){
        m_Logger->Log("Invalid number: " + number, Logger::LogLevelError, Logger::LogConsoleFile);
        return false;
    }

    m_Number = number;

    return true;
}

void Rider::SetFirstName(const std::string &firstName) {
    m_FirstName = firstName;
}

void Rider::SetLastName(const std::string &lastName) {
    m_LastName = lastName;
}

std::string Rider::GetFirstName() {
    return m_FirstName;
}

std::string Rider::GetLastName() {
    return m_LastName;
}

std::string Rider::GetNumber() {
    return m_Number;
}

std::string Rider::GetCountry() {
    return m_Country;
}

std::string Rider::GetTeam() {
    return m_Team;
}

Rider &Rider::operator=(const Rider &rider) = default;

bool Rider::operator==(const Rider &rider) {
    return std::stoi(m_Number) == std::stoi(rider.m_Number);
}

bool Rider::operator!=(const Rider &rider) {
    return std::stoi(m_Number) != std::stoi(rider.m_Number);
}

bool Rider::operator<(const Rider &rider) {
    return std::stoi(m_Number) < std::stoi(rider.m_Number);
}

bool Rider::operator<=(const Rider &rider) {
    return std::stoi(m_Number) <= std::stoi(rider.m_Number);
}

bool Rider::operator>(const Rider &rider) {
    return std::stoi(m_Number) > std::stoi(rider.m_Number);
}

bool Rider::operator>=(const Rider &rider) {
    return std::stoi(m_Number) >= std::stoi(rider.m_Number);
}
