#ifndef MOTOGP_FANTASY_LEAGUE_RIDER_MANAGER_H
#define MOTOGP_FANTASY_LEAGUE_RIDER_MANAGER_H

#include <iostream>
#include "rider.h"

class RiderManager{
private:
    Rider rider;
    int points;
    int position;
public:
    RiderManager();
    ~RiderManager();

    Rider& getRider();
    int getPoints();
    int getPosition();

    void setRider(Rider rider);
    void setPoints(int points);
    void setPosition(int position);

    string toString();
    string toStringIndexed(int index);
    string toStringSmall(bool spacing);
    string toStringSmallFullName();
    string toStringDisk();

    RiderManager& operator=(const RiderManager &riderManager);
    bool operator==(const RiderManager &riderManager);
    bool operator!=(const RiderManager &riderManager);
    bool operator<=(const RiderManager &riderManager);
    bool operator>=(const RiderManager &riderManager);
    bool operator<(const RiderManager &riderManager);
    bool operator>(const RiderManager &riderManager);
};

#endif //MOTOGP_FANTASY_LEAGUE_RIDER_MANAGER_H
