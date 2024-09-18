#ifndef MOTOGP_FANTASY_LEAGUE_MODERN_RIDERMANAGER_H
#define MOTOGP_FANTASY_LEAGUE_MODERN_RIDERMANAGER_H

#include "Rider.h"
#include "Util.h"

class RiderManager {
private:
    Rider m_Rider;
    int m_Points;
    int m_Position;
public:
    RiderManager();

    void SetRider(Rider rider);
    bool SetPoints(int points);
    bool SetPosition(int position);

    Rider& GetRider();
    int GetPoints();
    int GetPosition();

    std::string ToString();
    std::string ToStringIndexed(int index);
    std::string ToStringSmall(bool spacing);
    std::string ToStringSmallFullName();
    std::string ToStringDisk();

    RiderManager& operator=(const RiderManager &riderManager);
    bool operator==(const RiderManager &riderManager);
    bool operator!=(const RiderManager &riderManager);
    bool operator<=(const RiderManager &riderManager);
    bool operator>=(const RiderManager &riderManager);
    bool operator<(const RiderManager &riderManager);
    bool operator>(const RiderManager &riderManager);
};


#endif //MOTOGP_FANTASY_LEAGUE_MODERN_RIDERMANAGER_H
