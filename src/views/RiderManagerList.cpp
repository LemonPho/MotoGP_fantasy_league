#include "views/RiderManagerList.h"

RiderManagerList::RiderManagerList() {
    m_Logger = std::make_shared<Logger>();
}

RiderManagerList::RiderManagerList(std::shared_ptr<Logger> logger) {
    m_Logger = logger;
}

std::vector<RiderManager> RiderManagerList::GetRiderManagerList() {
    return m_RiderManagerList;
}

bool RiderManagerList::SetRiderManager(RiderManager riderManager, size_t index){
    size_t duplicates = 0;
    for (auto& tempRiderManager : m_RiderManagerList) {
        if (tempRiderManager == riderManager) {
            duplicates++;
        }
    }

    if (duplicates >= 1) {
        m_Logger->Log("Rider already exists in list", Logger::LogLevelError, Logger::LogFile);
        return false;
    } else {
        m_RiderManagerList[index] = riderManager;
        return true;
    }
}

void RiderManagerList::AddRiderManager(RiderManager riderManager) {
    m_RiderManagerList.push_back(riderManager);
}

void RiderManagerList::RemoveRiderManager(RiderManager riderManager) {
    m_RiderManagerList.erase(std::remove(m_RiderManagerList.begin(), m_RiderManagerList.end(), riderManager), m_RiderManagerList.end());
}

RiderManager RiderManagerList::FindRiderManager(RiderManager riderManager) {
    for(auto tempRiderManager : m_RiderManagerList){
        if(tempRiderManager == riderManager){
            return tempRiderManager;
        }
    }

    RiderManager tempRiderManager;

    return tempRiderManager;
}

RiderManager RiderManagerList::GetRiderManagerIndex(size_t index) {
    return m_RiderManagerList[index];
}

std::vector<std::string> RiderManagerList::ToStringVector() {
    std::vector<std::string> result;

    for(auto& riderManager : m_RiderManagerList){
        result.push_back(riderManager.ToString());
    }

    return result;
}

std::string RiderManagerList::ToStringSmall(bool spacing) {
    std::string result = "";

    for (auto& riderManager : m_RiderManagerList) {
        result += riderManager.ToStringSmall(spacing) + " ";
    }

    return result;
}

std::string RiderManagerList::ToStringHTML() {
    std::string result = "";

    for (auto& riderManager : m_RiderManagerList) {
        result += "<td>" + riderManager.ToStringSmall(false) + "</td>";
    }

    return result;
}

void RiderManagerList::WriteToDisk(const std::filesystem::path &fileName) {
    std::ofstream file(fileName);
    std::string tempString;

    if(!file.is_open()){
        m_Logger->Log("Could not open the file at: " + fileName.string() + " to save the rider list", Logger::LogLevelError, Logger::LogConsoleFile);
        return;
    }

    for(auto i: m_RiderManagerList){
        tempString = i.ToStringDisk();
        file << tempString << std::endl;
    }

    file.close();
    m_Logger->Log("Rider list successfully saved", Logger::LogLevelSuccess, Logger::LogFile);
}

void RiderManagerList::ReadFromDisk(const std::filesystem::path &fileName) {
    m_Logger->Log("Reading rider list from disk", Logger::LogLevelInfo, Logger::LogFile);
    std::ifstream file(fileName);
    std::string tempString;

    std::string firstName, lastName, country, team, number;
    int points;

    if(!file.is_open()){
        m_Logger->Log("Couldn't open the file at: " + fileName.string() + " to load the rider list", Logger::LogLevelError, Logger::LogConsoleFile);
        return;
    }

    std::getline(file, tempString, '|');
    if(tempString.empty() || tempString == " "){
        m_Logger->Log("Rider list file empty", Logger::LogLevelInfo, Logger::LogFile);
        return;
    }

    while(tempString != " " && !tempString.empty()){
        std::shared_ptr<Rider> tempRider = std::make_shared<Rider>(m_Logger);
        RiderManager tempRiderManager(m_Logger);
        number = tempString;
        getline(file, tempString, '|');
        firstName = tempString;
        getline(file, tempString, '|');
        lastName = tempString;
        getline(file, tempString, '|');
        country = tempString;
        getline(file, tempString, '|');
        team = tempString;
        getline(file, tempString, '|');
        points = stoi(tempString);
        getline(file, tempString);
        tempRider->SetData(firstName, lastName, number, country, team);
        tempRiderManager.SetRider(tempRider);
        tempRiderManager.SetPoints(points);
        m_RiderManagerList.push_back(tempRiderManager);
        getline(file, tempString, '|');
    }

    m_Logger->Log("Rider list successfully read from file", Logger::LogLevelSuccess, Logger::LogFile);
}
