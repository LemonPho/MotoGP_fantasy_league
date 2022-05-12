#ifndef MOTOGP_FANTASY_LEAGUE_MEMBER_LIST_H
#define MOTOGP_FANTASY_LEAGUE_MEMBER_LIST_H

#include <iostream>
#include <fstream>

#include "member-node.h"
#include "rider-list.h"

using namespace std;

class MemberList {
    MemberNode* header;
    bool isValidPos(MemberNode* memberNode);
public:
    RiderList* riderList;

    MemberList();
    ~MemberList();

    bool isEmpty();
    void insertData(MemberNode* memberNode, const Member& data);
    void deleteData(MemberNode* memberNode);
    MemberNode* getFirstPos();
    MemberNode* getLastPos();
    MemberNode* getNextPos(MemberNode *memberNode);
    void sortMembers();
    string toString();
    void deleteAll();
    void writeToDisk(const string &fileName);
    MemberList* readFromDisk(const string &fileName);
};

#endif //MOTOGP_FANTASY_LEAGUE_MEMBER_LIST_H
