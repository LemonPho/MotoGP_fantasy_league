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

    std::vector<RiderManager> GetRiderManagerList();

    void AddRiderManager(RiderManager riderManager);
    void RemoveRiderManager(RiderManager riderManager);

    RiderManager FindRiderManager(RiderManager riderManager);
    RiderManager GetRiderManagerIndex(size_t index);

    std::vector<std::string> ToStringVector();

    void WriteToDisk(const std::filesystem::path &fileName);
    void ReadFromDisk(const std::filesystem::path &fileName);
};


#endif //MOTOGP_FANTASY_LEAGUE_MODERN_RIDERMANAGERLIST_H
