#ifndef MOTOGP_FANTASY_LEAGUE_RIDER_NODE_H
#define MOTOGP_FANTASY_LEAGUE_RIDER_NODE_H

#include <iostream>
#include "rider.h"

class RiderNode {
private:
    Rider data;
    RiderNode* next;
public:
    RiderNode();
    RiderNode(const Rider &rider);

    Rider getData();
    RiderNode* getNext();
    void setData(const Rider &data);
    void setNext(RiderNode* riderNode);
};

#endif //MOTOGP_FANTASY_LEAGUE_RIDER_NODE_H
