#ifndef MOTOGP_FANTASY_LEAGUE_MODERN_MEMBERLIST_H
#define MOTOGP_FANTASY_LEAGUE_MODERN_MEMBERLIST_H

#include <iostream>
#include <vector>
#include <algorithm>

#include "Member.h"
#include "Logger.h"
#include "RiderManagerList.h"

class MemberList {
private:
    std::vector<Member> m_MemberList;
    std::shared_ptr<Logger> m_Logger;
public:
    MemberList();
    explicit MemberList(std::shared_ptr<Logger> logger);

    void AddMember(Member member);
    void RemoveMember(Member member);
    void DeleteAllMembers();

    std::string ToString();
    std::string ToStringSmallHTML();

    void SortMembers();
    void UpdateMembersPoints();

    void WriteToDisk(const std::filesystem::path &fileName);
    void ReadFromDisk(const std::filesystem::path &fileName, RiderManagerList riderManagerList);

};


#endif //MOTOGP_FANTASY_LEAGUE_MODERN_MEMBERLIST_H
