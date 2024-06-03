#ifndef MOTOGP_FANTASY_LEAGUE_RACE_RESULT_SCRAPER_H
#define MOTOGP_FANTASY_LEAGUE_RACE_RESULT_SCRAPER_H

#include <iostream>
#include <curl/curl.h>
#include <libxml/HTMLparser.h>
#include <fstream>
#include <cstdio>

#include "util.h"
#include "rider-list.h"

#define RACE_RESULT_HTML_FILE "tempresults.html"

using namespace std;

class RaceResultScraper{
private:
    Rider *riders;
    int ridersIndex=0;
    string url;
    string buffer;
public:
    RaceResultScraper(RiderList *riderList, const string url);
    ~RaceResultScraper();

    int getRidersIndex();
    Rider getRider(int index);
    string getUrl();
    string getBuffer();

    static size_t writeBuffer(void* contents, size_t size, size_t nmemb, void* userp);
    bool get();
    bool saveHTML();
    bool deleteHTML();
    bool parseHTML();
    xmlNode* findTableBody(xmlNode* node);
    xmlNode* traverseTable(xmlNode* node);
    bool saveRiderResult();
};

#endif //MOTOGP_FANTASY_LEAGUE_RACE_RESULT_SCRAPER_H
