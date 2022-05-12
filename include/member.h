#ifndef MOTOGP_FANTASY_LEAGUE_MEMBER_H
#define MOTOGP_FANTASY_LEAGUE_MEMBER_H

#include <iostream>

#include "rider.h"

using namespace std;

#define RIDER_COUNT 5
#define SPACE_USERNAME 30
#define MAX_USERNAME 20

class Member {
private:
    string userName;
    Rider riders[RIDER_COUNT];
    Rider rookie;
    int riderCount;
    int points;

public:
    Member();
    Member(const Member &member);

    bool setUserName(string &userName);
    void setRider(Rider &rider);
    void setRiderCount(int &riderCount);
    void setRookie(Rider &rookie);
    void setPoints(int &points);

    string getUserName();
    Rider getRider(int &index);
    Rider getRookie();
    int getRiderCount();
    int getPoints();

    string getRidersDisk();
    string toStringSmall();

    Member &operator = (const Member member1);
};

#endif //MOTOGP_FANTASY_LEAGUE_MEMBER_H
