#ifndef MOTOGP_FANTASY_LEAGUE_MODERN_RIDERMANAGER_H
#define MOTOGP_FANTASY_LEAGUE_MODERN_RIDERMANAGER_H

#include <iostream>
#include <memory>
#include <vector>
#include <fstream>

#include "Rider.h"
#include "Util.h"
#include "Logger.h"

class RiderManager {
private:
    std::shared_ptr<Rider> m_Rider;
    std::shared_ptr<Logger> m_Logger;
    int m_Points;
    int m_Position;
public:
    RiderManager();
    explicit RiderManager(std::shared_ptr<Logger> logger);
    RiderManager(std::shared_ptr<Rider> rider, std::shared_ptr<Logger> m_Logger);

    void SetLogger(std::shared_ptr<Logger> logger);
    void SetRider(std::shared_ptr<Rider> rider);
    bool SetPoints(int points);
    bool SetPosition(int position);

    std::shared_ptr<Rider> GetRiderPtr();
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
