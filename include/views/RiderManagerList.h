#ifndef MOTOGP_FANTASY_LEAGUE_MODERN_RIDERMANAGERLIST_H
#define MOTOGP_FANTASY_LEAGUE_MODERN_RIDERMANAGERLIST_H

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

#include "models/RiderManager.h"
#include "core/Logger.h"

class RiderManagerList {
private:
    std::vector<RiderManager> m_RiderManagerList;
    std::shared_ptr<Logger> m_Logger;
public:
    RiderManagerList();
    explicit RiderManagerList(std::shared_ptr<Logger> logger);

    std::vector<RiderManager> GetRiderManagerList();

    bool SetRiderManager(RiderManager riderManager, size_t index, bool checkDuplicates);
    void AddRiderManager(RiderManager riderManager);
    void RemoveRiderManager(RiderManager riderManager);

    RiderManager FindRiderManager(RiderManager riderManager);
    RiderManager GetRiderManagerIndex(size_t index);

    std::vector<std::string> ToStringVector();
    std::string ToStringSmall(bool spacing);
    std::string ToStringHTML();

    void WriteToDisk(const std::filesystem::path &fileName);
    void ReadFromDisk(const std::filesystem::path &fileName);
};


#endif //MOTOGP_FANTASY_LEAGUE_MODERN_RIDERMANAGERLIST_H
