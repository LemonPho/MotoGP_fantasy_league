#ifndef MOTOGP_FANTASY_LEAGUE_RIDER_MANAGER_H
#define MOTOGP_FANTASY_LEAGUE_RIDER_MANAGER_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include "rider.h"

class RiderManager{
private:
    Rider rider;
    float points;
    int position;
public:
    RiderManager();
    ~RiderManager();

    Rider& getRider();
    float getPoints();
    int getPosition();

    void setRider(Rider rider);
    void setPoints(float points);
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
