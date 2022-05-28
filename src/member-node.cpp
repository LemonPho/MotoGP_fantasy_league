#include "member-node.h"

MemberNode::MemberNode()
    :dataPointer(nullptr),
    next(nullptr),
    previous(nullptr)
{}

MemberNode::MemberNode(const Member &data) {
    dataPointer = new Member(data);
    next = nullptr;
    previous = nullptr;
}

MemberNode::~MemberNode() {
    delete dataPointer;
}

void MemberNode::setData(Member data) {
    Member* tempMember = new Member();
    *tempMember = data;
    dataPointer = tempMember;
}

void MemberNode::setNext(MemberNode *next) {
    this->next = next;
}

void MemberNode::setPrevious(MemberNode *previous) {
    this->previous = previous;
}

Member MemberNode::getData() {
    return *dataPointer;
}

Member *MemberNode::getDataPointer() {
    return dataPointer;
}

MemberNode *MemberNode::getNext() {
    return next;
}

MemberNode *MemberNode::getPrevious() {
    return previous;
}
