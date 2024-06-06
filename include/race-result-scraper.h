#ifndef MOTOGP_FANTASY_LEAGUE_RACE_RESULT_SCRAPER_H
#define MOTOGP_FANTASY_LEAGUE_RACE_RESULT_SCRAPER_H

#include <iostream>
#include <curl/curl.h>
#include <libxml/HTMLparser.h>
#include <fstream>
#include <cstdio>

#include "util.h"
#include "rider-list.h"
#include "race-result.h"
#include "race-result-list.h"

#define RACE_RESULT_HTML_FILE "tempresults.html"

using namespace std;

class RaceResultScraper{
private:
    RaceResult raceResult;
    RiderManager tempRider;

    string url;
    string buffer;

    ErrorMessage *errorMessage;
public:
    RaceResultScraper();
    explicit RaceResultScraper(ErrorMessage *errorMessage);
    RaceResultScraper(string url, ErrorMessage *errorMessage);
    ~RaceResultScraper();

    RaceResult getRaceResult();
    bool getUrlIsSprint();

    string getUrl();
    string getBuffer();

    string trimSpaces(string source);

    //retrieval and generation of the race result
    bool generateRaceResult(RiderList *riderList);
    static size_t writeBuffer(void* contents, size_t size, size_t nmemb, void* userp);
    static size_t writeNothing(void* contents, size_t size, size_t nmemb, void* userp);
    bool retrieveResults();
    bool saveHTML();
    bool deleteHTML();
    bool parseHTML(RiderList* riderList);
    xmlNode* findRaceTitle(xmlNode* node);
    xmlNode* findTableBody(xmlNode* node);
    xmlNode* traverseTable(xmlNode* node);
    void generateRiderPositions(xmlNode* node, RiderList* riderList);

    void addRacePointsToRiderList(RiderList* riderList);

    //vector<RiderManager> saveRaceResult(RiderList* riderList);
};

#endif //MOTOGP_FANTASY_LEAGUE_RACE_RESULT_SCRAPER_H
