#include "member-list.h"

bool MemberList::isValidPos(MemberNode *memberNode) {
    MemberNode* temp(header);

    while(temp != nullptr){
        if(temp == memberNode) {
            return true;
        }
        temp = temp->getNext();
    }
    return false;
}

MemberList::MemberList() : header(nullptr){
    riderList = new RiderList();
}

MemberList::~MemberList() {
    deleteAll();
    delete header;
}

bool MemberList::isEmpty() {
    return header == nullptr;
}

void MemberList::insertData(MemberNode *memberNode, const Member &data) {
    if(memberNode != nullptr && !isValidPos(memberNode)){
        cout << "Invalid position when inserting member, try again after restart" << endl;
        throw exception();
    }

    if(memberNode == nullptr){
        memberNode = header;
    }

    MemberNode* toInsert(new MemberNode(data));

    if(toInsert == nullptr){
        cout << "No more space found for program, maybe out of system ram" << endl;
        throw exception();
    }

    toInsert->setNext(header);
    toInsert->setPrevious(nullptr);

    if(header != nullptr){
        header->setPrevious(toInsert);
    }
    header = toInsert;
}

void MemberList::deleteData(MemberNode *memberNode) {
    MemberNode* temp(header);

    if(memberNode == nullptr){
        cout << "Error when deleting, member doesn't exist" << endl;
        throw exception();
    } else if(temp == nullptr){
        return;
    }

    if(temp == memberNode){
        header = header->getNext();
        free(memberNode);
        return;
    }

    if(memberNode == getLastPos()){
        temp = memberNode;
        temp = temp->getPrevious();
        temp->setNext(nullptr);
        free(memberNode);
        return;
    }

    if(memberNode != header && memberNode != getLastPos()){
        while(temp != memberNode){
            temp = temp->getNext();
        }
        if(temp == memberNode){
            temp->getNext()->setPrevious(temp->getPrevious());
            temp->getPrevious()->setNext(temp->getNext());
            free(memberNode);
        }
    }
}

MemberNode *MemberList::getFirstPos() {
    if(!isEmpty()){
        return header;
    } else {
        return nullptr;
    }
}

MemberNode *MemberList::getLastPos() {
    if(!isEmpty()) {
        MemberNode *temp;
        temp = header;
        while (temp != nullptr){
            if(getNextPos(temp) == nullptr){
                return temp;
            } else {
                temp = temp->getNext();
            }
        }
    }
    return nullptr;
}

MemberNode *MemberList::getNextPos(MemberNode *memberNode) {
    return memberNode->getNext();
}

void MemberList::sortMembers() {

}

string MemberList::toString() {
    MemberNode* temp(header);
    MemberNode* last(getLastPos());
    string result;

    while(temp != nullptr){
        result += temp->getData().toStringSmall();
        if(temp != last) {
            result += "\n";
        }
        temp = temp->getNext();
    }

    return result;
}

void MemberList::deleteAll() {
    MemberNode* temp(header);
    MemberNode* prev;

    while(temp != nullptr){
        prev = temp;
        temp = temp->getNext();
        delete prev;
    }
    header = nullptr;
}

void MemberList::writeToDisk(const string &fileName) {
    ofstream file(fileName, ios::out);
    MemberNode* temp(header);
    string tempString;

    if(!file.is_open()){
        cout << "Couldn't open " << fileName << endl;
        return;
    }
    while(temp != nullptr){
        tempString = temp->getData().getUserName();
        tempString += "|";
        tempString += to_string(temp->getData().getRiderCount());
        tempString += "|";
        tempString += to_string(temp->getData().getPoints());
        tempString += "|";
        tempString += temp->getData().getRookie().toStringDisk();
        tempString += "|";
        tempString += temp->getData().getRidersDisk();
        file << tempString << endl;
        temp = temp->getNext();
    }
}

MemberList *MemberList::readFromDisk(const string &fileName) {
    return nullptr;
}
