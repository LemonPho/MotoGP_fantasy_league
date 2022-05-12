#include "rider-node.h"

RiderNode::RiderNode() {
    data = Rider();
    next = nullptr;
}

RiderNode::RiderNode(const Rider &rider) {
    data = rider;
    next = nullptr;
}

Rider RiderNode::getData() {
    return data;
}

RiderNode *RiderNode::getNext() {
    return next;
}

void RiderNode::setData(const Rider &data) {
    this->data = data;
}

void RiderNode::setNext(RiderNode *riderNode) {
    next = riderNode;
}
