#ifndef MOTOGP_FANTASY_LEAGUE_RACE_RESULT_LIST_H
#define MOTOGP_FANTASY_LEAGUE_RACE_RESULT_LIST_H

#include <iostream>
#include <vector>
#include <fstream>

#include "race-result.h"
#include "error-message.h"

class RaceResultList{
private:
    vector<RaceResult> raceResults;

    ErrorMessage *errorMessage;
public:
    RaceResultList();
    RaceResultList(ErrorMessage *errorMessage);
    ~RaceResultList();

    void pushRaceResult(RaceResult raceResult);
    void eraseRaceResult(int index);
    vector<RaceResult> getRaceResults();

    string toString();
    string toStringSmallWithIndex();
    string toStringDisk();

    void readFromDisk(const string &filename, RiderList* riderList);
    void writeToDisk(const string &filename);

    RaceResultList& operator=(RaceResultList raceResultList);
};

#endif //MOTOGP_FANTASY_LEAGUE_RACE_RESULT_LIST_H
