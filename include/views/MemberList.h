#ifndef MOTOGP_FANTASY_LEAGUE_MODERN_MEMBERLIST_H
#define MOTOGP_FANTASY_LEAGUE_MODERN_MEMBERLIST_H

#include <iostream>
#include <vector>
#include <algorithm>

#include "models/Member.h"
#include "core/Logger.h"
#include "views/RiderManagerList.h"

class MemberList {
private:
    std::vector<Member> m_MemberList;
    std::shared_ptr<Logger> m_Logger;
public:
    MemberList();
    explicit MemberList(std::shared_ptr<Logger> logger);

    void SetMember(Member member, size_t index);
    void AddMember(Member member);
    void RemoveMember(Member member);
    bool DeleteAllMembers();

    std::vector<Member> GetMemberList();

    std::string ToString();
    std::vector<std::string> ToStringArray();
    std::string ToStringSmallHTML();

    void SortMembers();
    void UpdateMembersPoints();

    void WriteToDisk(const std::filesystem::path &fileName);
    void ReadFromDisk(const std::filesystem::path &fileName, RiderManagerList riderManagerList);

};


#endif //MOTOGP_FANTASY_LEAGUE_MODERN_MEMBERLIST_H
