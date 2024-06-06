#ifndef MOTOGP_FANTASY_LEAGUE_RIDER_NODE_H
#define MOTOGP_FANTASY_LEAGUE_RIDER_NODE_H

#include <iostream>
#include "rider.h"
#include "rider-manager.h"

class RiderNode {
private:
    RiderManager data;
    RiderNode* next;
    RiderNode* previous;
public:
    RiderNode();
    explicit RiderNode(const RiderManager &riderManager);

    RiderManager getData();
    RiderManager* getDataReference();
    RiderNode* getNext();
    RiderNode* getPrevious();
    void setData(const RiderManager &data);
    void setNext(RiderNode* riderNode);
    void setPrevious(RiderNode* riderNode);
};

#endif //MOTOGP_FANTASY_LEAGUE_RIDER_NODE_H
