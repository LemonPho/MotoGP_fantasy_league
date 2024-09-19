#ifndef MOTOGP_FANTASY_LEAGUE_MODERN_RIDERMANAGERLIST_H
#define MOTOGP_FANTASY_LEAGUE_MODERN_RIDERMANAGERLIST_H

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

#include "RiderManager.h"
#include "Logger.h"

class RiderManagerList {
private:
    std::vector<RiderManager> m_RiderManagerList;
    std::shared_ptr<Logger> m_Logger;
public:
    RiderManagerList();
    explicit RiderManagerList(std::shared_ptr<Logger> logger);

    void AddRiderManager(RiderManager riderManager);
    void RemoveRiderManager(RiderManager riderManager);

    void WriteToDisk(const std::filesystem::path &fileName);
    void ReadFromDisk(const std::filesystem::path &fileName);
};


#endif //MOTOGP_FANTASY_LEAGUE_MODERN_RIDERMANAGERLIST_H
