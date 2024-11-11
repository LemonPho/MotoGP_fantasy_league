#include "views/MemberList.h"

MemberList::MemberList() {
    m_Logger = std::make_shared<Logger>();
}

MemberList::MemberList(std::shared_ptr<Logger> logger) {
    m_Logger = logger;
}

void MemberList::SetMember(Member member, size_t index){
    m_MemberList[index] = member;
    SortMembers(true);
}

void MemberList::AddMember(Member member) {
    m_MemberList.push_back(member);
    SortMembers(true);
}

void MemberList::RemoveMember(Member member) {
    m_MemberList.erase(std::remove(m_MemberList.begin(), m_MemberList.end(), member), m_MemberList.end());
    m_Logger->Log("Member " + member.GetMemberUserName() + " was deleted", Logger::LogLevelSuccess, Logger::LogConsoleFile);
    SortMembers(true);
}

std::vector<Member> MemberList::GetMemberList(){
    return m_MemberList;
}

std::string MemberList::ToString() {
    if(m_MemberList.empty()){
        m_Logger->Log("Member list empty", Logger::LogLevelWarning, Logger::LogConsoleFile);
        return "";
    }

    std::string result;

    for(auto member : m_MemberList){
        result += member.ToStringSmall() + "\n";
    }

    return result;
}

std::vector<std::string> MemberList::ToStringArray() {
    std::vector<std::string> result;

    for(auto member : m_MemberList){
        result.push_back(member.GetMemberUserName());
    }

    return result;
}

std::string MemberList::ToStringSmallHTML() {
    if(m_MemberList.empty()){
        m_Logger->Log("Member list empty", Logger::LogLevelWarning, Logger::LogConsoleFile);
        return "";
    }

    std::string result;

    result += "<table>";

    int position = 1;
    for(auto member : m_MemberList){
        std::ostringstream stream;
        result += "<tr>";
        result += "<td>";
        result += "<b>";
        result += std::to_string(position);
        result += ". ";
        result += member.GetMemberUserName();
        result += " - ";
        stream << std::fixed << std::setprecision(2) << member.GetPoints();
        result += stream.str();
        result += "</b>";
        result += "</td>";
        result += member.GetRiderList().ToStringHTML();
        result += "</tr>\n";
        position++;
    }

    result += "</table>";

    return result;
}

void MemberList::SortMembers(bool updatePoints) {
    if (updatePoints) {
        UpdateMembersPoints();
    }
    m_Logger->Log("Sorting members", Logger::LogLevelInfo, Logger::LogFile);
    std::sort(m_MemberList.rbegin(), m_MemberList.rend());
    m_Logger->Log("Sorted members", Logger::LogLevelInfo, Logger::LogFile);
}

void MemberList::UpdateMembersPoints() {
    m_Logger->Log("Updating members points", Logger::LogLevelInfo, Logger::LogFile);
    int points=0;
    for(auto& member : m_MemberList){
        points = 0;
        for(auto& rider : member.GetRiderList().GetRiderManagerList()){
            points += rider.GetPoints();
        }

        member.SetPoints(points);
    }
    m_Logger->Log("Updated members points", Logger::LogLevelInfo, Logger::LogFile);
}

void MemberList::AddFinalizedPoints(RiderManagerList& riderManagerList) {
    float finalPoints;
    float pointsMultipliers[] = { 0.1, 0.07, 0.05, 0.0325, 0.02 };
    Member member;
    RiderManagerList memberRiderManagerList;

    for (size_t i = 0; i < m_MemberList.size(); i++) {
        member = m_MemberList[i];
        memberRiderManagerList = member.GetRiderList();
        finalPoints = member.GetPoints();
        for (size_t j = 0; j < Member::RIDER_COUNT - 1; j++) {
            if (memberRiderManagerList.GetRiderManagerIndex(j) == riderManagerList.GetRiderManagerIndex(j)) {
                finalPoints += riderManagerList.GetRiderManagerIndex(j).GetPoints() * pointsMultipliers[j];
            }
        }

        member.SetPoints(finalPoints);
    }
}

bool MemberList::DeleteAllMembers() {
    if(m_MemberList.empty()){
        m_Logger->Log("Member list empty", Logger::LogLevelWarning, Logger::LogConsoleFile);
        return false;
    }

    m_MemberList.clear();
    std::vector<Member> emptyMemberList;
    m_MemberList.swap(emptyMemberList);

    m_Logger->Log("Members deleted", Logger::LogLevelSuccess, Logger::LogConsoleFile);
    return true;
}

void MemberList::WriteToDisk(const std::filesystem::path &fileName) {
    m_Logger->Log("Writing member list changes to disk", Logger::LogLevelInfo, Logger::LogFile);
    std::ofstream file(fileName, std::ios::out);
    std::string tempString;

    if(!file.is_open()){
        m_Logger->Log("File couldn't be opened to save member data: " + fileName.string(), Logger::LogLevelError, Logger::LogConsoleFile);
        return;
    }

    for(auto i : m_MemberList){
        tempString = i.GetMemberUserName();
        tempString += "|";
        for(auto j : i.GetRiderList().GetRiderManagerList()){
            tempString += j.GetRider().GetNumber();
            tempString += "|";
        }

        file << tempString << std::endl;
    }

    file.close();
    m_Logger->Log("Member data successfully saved", Logger::LogLevelSuccess, Logger::LogConsoleFile);
}

void MemberList::ReadFromDisk(const std::filesystem::path &fileName, RiderManagerList riderManagerList) {
    m_Logger->Log("Reading member list from disk", Logger::LogLevelInfo, Logger::LogFile);
    std::ifstream file(fileName);
    std::string tempString;

    std::string userName, independentNumber, number;
    std::shared_ptr<Rider> tempRider = std::make_shared<Rider>(m_Logger);
    int pointsMember = 0;

    if(!file.is_open()){
        m_Logger->Log("Couldn't open file to read member data at: " + fileName.string(), Logger::LogLevelError, Logger::LogConsoleFile);
        return;
    }

    std::getline(file, tempString, '|');
    if(tempString.empty() || tempString == " " || tempString == "\n"){
        m_Logger->Log("Member data file empty", Logger::LogLevelInfo, Logger::LogFile);
        return;
    }

    while(tempString != " " && !tempString.empty()){
        Member tempMember(m_Logger);
        int i;
        userName = tempString;
        tempMember.SetUserName(userName);
        for(i = 0; i < Member::RIDER_COUNT; i++){
            RiderManager tempRiderManager(m_Logger);
            getline(file, tempString, '|');
            number = tempString;
            tempRider->SetNumber(number);
            tempRiderManager.SetRider(tempRider);
            tempRiderManager = riderManagerList.FindRiderManager(tempRiderManager);
            tempRiderManager.SetPosition(i+1);
            if(tempRiderManager.GetRiderPtr() == nullptr){
                m_Logger->Log("Could not find rider #" + number, Logger::LogLevelError, Logger::LogConsoleFile);
            } else {
                tempMember.InsertRiderManager(tempRiderManager);
            }
        }
        tempMember.SetPoints(pointsMember);
        m_MemberList.push_back(tempMember);
        getline(file, tempString);
        getline(file, tempString, '|');
        tempMember = Member(m_Logger);
    }

    SortMembers(true);
    m_Logger->Log("Successfully read member list from disk", Logger::LogLevelSuccess, Logger::LogFile);
}
