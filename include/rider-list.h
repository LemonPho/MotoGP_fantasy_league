#ifndef MOTOGP_FANTASY_LEAGUE_RIDER_LIST_H
#define MOTOGP_FANTASY_LEAGUE_RIDER_LIST_H

#include <iostream>
#include <fstream>
#include <vector>

#include "rider-node.h"
#include "error-message.h"
#include "rider-manager.h"

class RiderList {
private:
    RiderNode* header;
    ErrorMessage* errorMessage;

    bool isValidPos(RiderNode* riderNode);
public:
    RiderList();
    RiderList(RiderNode *header, ErrorMessage *errorMessage);
    ~RiderList();

    void setErrorMessage(ErrorMessage *errorMessage);

    bool isEmpty();
    int riderCount();
    void insertData(RiderNode* riderNode, const RiderManager &data);
    void insertOrdered(RiderManager& data);
    void deleteData(RiderNode* riderNode);
    void generatePositions(); //should be called after riders are inserted
    RiderNode* getFirstPos();
    RiderNode* getLastPos();
    RiderNode* getNextPos(RiderNode *riderNode);
    RiderNode* retrievePos(RiderManager& riderManager);
    RiderNode* retrievePosIndex(int index);
    RiderManager retrieveData(RiderNode* riderNode);
    string toString();
    string toStringIndexed();
    void deleteAll();
    void writeToDisk(const string& fileName);
    RiderList* copyFromDisk(const string& fileName);
    void modifyFromDisk(const string &fileName);

    vector<RiderManager> copyToVector();

    RiderList& deepCopy(RiderList *riderList);
    RiderList& operator = (RiderList* riderList);
};

#endif //MOTOGP_FANTASY_LEAGUE_RIDER_LIST_H
