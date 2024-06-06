#ifndef MOTOGP_FANTASY_LEAGUE_RACE_RESULT_H
#define MOTOGP_FANTASY_LEAGUE_RACE_RESULT_H

#include <iostream>
#include <vector>

#include "rider-list.h"
#include "error-message.h"

//define doesn't support arrays
const int POINTS_RAC[] = {25, 20, 16, 13, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
const int POINTS_SPR[] = {12, 9, 7, 6, 5, 4, 3, 2, 1};
const int LIMIT_RAC = 15;
const int LIMIT_SPR = 9;

#define AMOUNT_RIDERS_SMALL_RESULTS 4

using namespace std;

class RaceResult{
private:
    vector<RiderManager> riderPositions;
    string name;
    bool isSprint;

    ErrorMessage *errorMessage;
public:
    RaceResult();
    explicit RaceResult(ErrorMessage *errorMessage);
    RaceResult(vector<RiderManager> riderList, string name, bool isSprint, ErrorMessage *errorMessage);
    ~RaceResult();

    void setName(const string &name);
    void setIsSprint(const bool &isSprint);
    void setRider(Rider rider, size_t index);
    void setRiderPositions(vector<RiderManager> riderPositions);

    vector<RiderManager> getRiderPositions();
    string& getName();
    bool& getIsSprint();

    void pushRiderPosition(RiderManager newRider);

    bool updateRiderList(RiderList* riderList);
    bool deleteRaceResult(RiderList* riderList);

    string toString();
    string toStringSmall();
    string toStringVerySmall();
    string toStringDisk();

    RaceResult& operator=(RaceResult raceResult);
};

#endif //MOTOGP_FANTASY_LEAGUE_RACE_RESULT_H
