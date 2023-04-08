#ifndef MOTOGP_FANTASY_LEAGUE_MEMBER_H
#define MOTOGP_FANTASY_LEAGUE_MEMBER_H

#include <iostream>

#include "rider.h"
#include "rider-list.h"

using namespace std;

#define RIDER_COUNT 6
#define SPACE_USERNAME 30
#define MAX_USERNAME 20

class Member {
private:
    string userName;
    RiderList *riderList;
    int points;

public:
    Member();
    Member(const Member &member);

    bool setUserName(string &userName);
    void insertRider(Rider &rider);
    void setRiderList(RiderList* riderList);
    void setPoints(int &points);

    string getUserName();
    RiderList* getRiderList();
    int getPoints();

    string toStringSmall();

    Member &operator = (const Member& member);
    bool operator == (const Member &member);
};

#endif //MOTOGP_FANTASY_LEAGUE_MEMBER_H
