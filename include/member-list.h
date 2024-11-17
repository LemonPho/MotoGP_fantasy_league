#ifndef MOTOGP_FANTASY_LEAGUE_MEMBER_LIST_H
#define MOTOGP_FANTASY_LEAGUE_MEMBER_LIST_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

#include "member-node.h"
#include "rider-list.h"
#include "error-message.h"

using namespace std;

class MemberList {
    MemberNode* header;
    ErrorMessage *errorMessage;

    bool isValidPos(MemberNode* memberNode);
public:

    MemberList();
    MemberList(ErrorMessage *errorMessage);
    MemberList(MemberNode* header, ErrorMessage *errorMessage);
    ~MemberList();

    void setErrorMessage(ErrorMessage *errorMessage);

    bool isEmpty();
    void insertData(MemberNode* memberNode, const Member& data);
    void deleteData(MemberNode* memberNode);
    MemberNode* getFirstPos();
    MemberNode* getLastPos();
    MemberNode* getNextPos(MemberNode *memberNode);
    MemberNode* retrievePos(const Member &data);
    void retrieveMemberPicks(RiderList *riderList);
    void updateMembersPoints();
    //this is a temporary solution, it returns an html table
    string addExtraMembersPoints(RiderList *riderList);
    //-------------
    void updateMembersRiders(RiderList *riderList);
    void sortMembers(RiderNode* riderHead);
    MemberNode* split(MemberNode* head);
    MemberNode* tieBreaker(MemberNode* first, MemberNode* second, RiderNode* riderHead);
    MemberNode* merge(MemberNode* first, MemberNode* second, RiderNode* riderHead);
    MemberNode* mergeSort(MemberNode* head, RiderNode* riderHead);
    string toString();
    string toStringSmallHTML();
    void deleteAll();
    void writeToDisk(const string &fileName);
    MemberList* copyFromDisk(const string &fileName);
    void modifyFromDisk(const string &fileName);

    MemberList& deepCopy(MemberList *memberList);
    MemberList& operator=(MemberList *memberList);
};

#endif //MOTOGP_FANTASY_LEAGUE_MEMBER_LIST_H
