
#ifndef MOTOGP_FANTASY_LEAGUE_MODERN_MEMBER_H
#define MOTOGP_FANTASY_LEAGUE_MODERN_MEMBER_H

#include <iostream>
#include <vector>

#include "models/RiderManager.h"
#include "views/RiderManagerList.h"
#include "core/Logger.h"

class Member {
public:
    enum AttributesIndexed {
        USERNAME_INDEX = 0,
        RIDER_LIST_INDEX,
        POINTS_INDEX,
    };

    enum Spacing {
        USERNAME_SPACING = 30,
    };

    enum Limits {
        RIDER_COUNT = 6,
        MAX_USERNAME = 20
    };
private:
    std::string m_UserName;
    RiderManagerList m_RiderList;
    std::shared_ptr<Logger> m_Logger;
    int m_Points;
public:
    Member();
    explicit Member(std::shared_ptr<Logger> logger);
    bool SetUserName(const std::string &userName);
    void InsertRiderManager(RiderManager &riderManager);
    void SetRiderList(RiderManagerList riderList);
    bool SetRiderManager(RiderManager riderManager, size_t index);
    bool SetPoints(int points);

    std::string GetMemberUserName();
    RiderManagerList GetRiderList();
    int GetPoints();

    std::string ToStringSmall();
    std::vector<std::string> ToStringEdit();

    Member& operator = (const Member& member);
    bool operator == (const Member& member);
    bool operator < (const Member& member);
};


#endif //MOTOGP_FANTASY_LEAGUE_MODERN_MEMBER_H
