#ifndef MOTOGP_FANTASY_LEAGUE_MEMBER_NODE_H
#define MOTOGP_FANTASY_LEAGUE_MEMBER_NODE_H

#include <iostream>

#include "member.h"

using namespace std;

class MemberNode {
private:
    Member* dataPointer;
    MemberNode* next;
    MemberNode* previous;

public:
    MemberNode();
    explicit MemberNode(const Member &data);
    ~MemberNode();

    void setData(Member data);
    void setNext(MemberNode* next);
    void setPrevious(MemberNode* previous);

    Member getData();
    Member* getDataReference();
    MemberNode* getNext();
    MemberNode* getPrevious();

};

#endif //MOTOGP_FANTASY_LEAGUE_MEMBER_NODE_H
