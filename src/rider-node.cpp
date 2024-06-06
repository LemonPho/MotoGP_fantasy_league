#include "rider-node.h"

RiderNode::RiderNode() {
    data = RiderManager();
    next = nullptr;
    previous = nullptr;
}

RiderNode::RiderNode(const RiderManager &riderManager) {
    data = riderManager;
    next = nullptr;
    previous = nullptr;
}

RiderManager RiderNode::getData() {
    return data;
}

RiderManager* RiderNode::getDataReference() {
    return &data;
}

RiderNode *RiderNode::getNext() {
    return next;
}

RiderNode *RiderNode::getPrevious() {
    return previous;
}

void RiderNode::setData(const RiderManager &data) {
    this->data = data;
}

void RiderNode::setNext(RiderNode *riderNode) {
    next = riderNode;
}

void RiderNode::setPrevious(RiderNode *riderNode) {
    previous = riderNode;
}
