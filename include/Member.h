
#ifndef MOTOGP_FANTASY_LEAGUE_MODERN_MEMBER_H
#define MOTOGP_FANTASY_LEAGUE_MODERN_MEMBER_H

#include <iostream>
#include <vector>

#include "RiderManager.h"
#include "Logger.h"

class Member {
public:
    static const int RIDER_COUNT = 6;
    const int SPACE_USERNAME = 30;
    const int MAX_USERNAME = 20;
private:
    std::string m_UserName;
    std::vector<RiderManager> m_RiderList;
    std::shared_ptr<Logger> m_Logger;
    int m_Points;
public:
    Member();
    explicit Member(std::shared_ptr<Logger> logger);
    bool SetUserName(const std::string &userName);
    void InsertRider(RiderManager &riderManager);
    void SetRiderList(std::vector<RiderManager> riderList);
    bool SetPoints(int points);

    std::string GetUserName();
    std::vector<RiderManager> GetRiderList();
    int GetPoints();

    std::string ToStringSmall();

    Member& operator = (const Member& member);
    bool operator == (const Member& member);
    bool operator < (const Member& member);
};


#endif //MOTOGP_FANTASY_LEAGUE_MODERN_MEMBER_H
