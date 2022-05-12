#ifndef MOTOGP_FANTASY_LEAGUE_MEMBER_H
#define MOTOGP_FANTASY_LEAGUE_MEMBER_H

#include <iostream>

#include "rider.h"

using namespace std;

#define RIDER_COUNT 5
#define SPACE_USERNAME 40

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
    void setRookie(Rider &rookie);
    void addPoints(int &points);

    string getUserName();
    Rider* getRiders();
    Rider getRookie();

    string toStringSmall();
};

#endif //MOTOGP_FANTASY_LEAGUE_MEMBER_H
