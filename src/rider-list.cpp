#include "rider-list.h"

bool RiderList::isValidPos(RiderNode *riderNode) {
    RiderNode* temp(header);
    while(temp != nullptr){
        if(temp == riderNode){
            return true;
        }
        temp = temp->getNext();
    }
    return false;
}

RiderList::RiderList() :header(nullptr) {}

RiderList::RiderList(RiderList &riderList) {}

RiderList::~RiderList() {
    delete header;
}

bool RiderList::isEmpty() {
    return header == nullptr;
}

void RiderList::insertData(RiderNode *riderNode, const Rider &data) {
    if(riderNode != nullptr && !isValidPos(riderNode)){
        cout << "Error when inserting data" << endl;
        throw exception();
    }

    RiderNode* toInsert(new RiderNode(data));

    if(toInsert == nullptr){
        cout << "No more space available, maybe allocation of ram for program is bad" << endl;
        throw exception();
    }
    if(riderNode == nullptr){
        toInsert->setNext(header);
        header = toInsert;
    } else {
        toInsert->setNext(riderNode->getNext());
        riderNode->setNext(toInsert);
    }
}

void RiderList::insertOrdered(Rider &data) {
    RiderNode* temp(header);
    RiderNode* prev(nullptr);

    while(temp != nullptr && data >= temp->getData()){
        prev = temp;
        temp = temp->getNext();
        if(temp != nullptr && data == temp->getData()){
            prev = temp;
            temp = temp->getNext();
        }
    }
    insertData(prev, data);
}



void RiderList::deleteData(RiderNode *riderNode) {
    RiderNode* temp(header);
    RiderNode* trail(nullptr);

    if(!isValidPos(riderNode)){
        cout << "Rider not found" << endl;
        getchar();
    }
    if(temp->getNext() == nullptr && temp == riderNode){
        free(header);
        header = nullptr;
    } else {
        while(temp != nullptr){
            if(temp == riderNode){
                trail->setNext(getNextPos(temp));
                temp = nullptr;
            } else {
                trail = temp;
                temp = temp->getNext();
            }
        }
        delete temp;
    }
}

RiderNode *RiderList::getFirstPos() {
    if(!isEmpty()){
        return header;
    } else {
        return nullptr;
    }
}

RiderNode *RiderList::getLastPos() {
    RiderNode* temp(header);

    if(isEmpty()){
        return nullptr;
    }

    if(getNextPos(temp) == nullptr){
        return temp;
    } else {
        while(temp != nullptr){
            if(getNextPos(temp) == nullptr){
                return temp;
            } else {
                temp = temp->getNext();
            }
        }
    }
    return nullptr;
}

RiderNode *RiderList::getNextPos(RiderNode* riderNode) {
    return riderNode->getNext();
}

RiderNode *RiderList::retrievePos(Rider &rider) {
    RiderNode* temp(header);
    RiderNode* last(getLastPos());

    if(temp == last){
        if(temp->getData() == rider){
            return temp;
        } else {
            return nullptr;
        }
    } else {
        while(temp != nullptr){
            if(temp->getData() == rider){
                return temp;
            }
            temp = temp->getNext();
        }
    }
    return nullptr;
}

Rider RiderList::retrieveData(RiderNode *riderNode) {
    RiderNode* temp(header);
    RiderNode* last(getLastPos());

    if(!isValidPos(riderNode)){
        return {};
    }

    return riderNode->getData();
}

string RiderList::toString() {
    RiderNode* temp(header);
    string result;

    if(isEmpty()){
        return "No riders in list";
    }

    while(temp != nullptr){
        result += temp->getData().toString();
        result += "\n";
        temp = temp->getNext();
    }

    return result;
}

void RiderList::deleteAll() {
    RiderNode* temp(header);
    RiderNode* trail(nullptr);
    RiderNode* last(getLastPos());

    if(temp == last){
        delete temp;
        header = new RiderNode();
    } else {
        while(temp != nullptr){
            trail = temp;
            temp = temp->getNext();
            delete trail;
        }
        delete temp;
    }
}

void RiderList::writeToDisk(const string &fileName) {

}

RiderList *RiderList::readFromDisk(const string &fileName) {
    return nullptr;
}
