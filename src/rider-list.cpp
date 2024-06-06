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

int RiderList::riderCount() {
    RiderNode* temp(header);
    int i = 0;

    while(temp != nullptr){
        i++;
        temp = temp->getNext();
    }

    return i;
}

RiderList::RiderList() :header(nullptr), errorMessage(nullptr){}

RiderList::RiderList(RiderNode *header, ErrorMessage *errorMessage) {
    this->header = header;
    this->errorMessage = errorMessage;
}

RiderList::~RiderList() {
    RiderNode* current = header;
    RiderNode* prev = new RiderNode();

    while(current != nullptr){
        prev = current;
        current = current->getNext();
        delete prev;
    }
}

void RiderList::setErrorMessage(ErrorMessage *errorMessage) {
    this->errorMessage = errorMessage;
}

bool RiderList::isEmpty() {
    return header == nullptr;
}

void RiderList::insertData(RiderNode *riderNode, const RiderManager &data) {
    if(riderNode != nullptr && !isValidPos(riderNode)){
        if(errorMessage != nullptr){
            errorMessage->addErrorMessage("Error when inserting data\n");
        }
        throw exception();
    }

    RiderNode* toInsert(new RiderNode(data));

    if(toInsert == nullptr){
        if(errorMessage != nullptr){
            errorMessage->addErrorMessage("No more ram space available");
        }
        throw exception();
    }

    if(header == nullptr){
        header = toInsert;
    }else if(riderNode == nullptr) {
        toInsert->setNext(header);
        header->setPrevious(toInsert);
        header = toInsert;
    }else if(riderNode->getNext() == nullptr) {
        riderNode->setNext(toInsert);
        toInsert->setPrevious(riderNode);
    } else {
        toInsert->setNext(riderNode->getNext());
        toInsert->setPrevious(riderNode);
        riderNode->getNext()->setPrevious(toInsert);
        riderNode->setNext(toInsert);
    }

}

void RiderList::insertOrdered(RiderManager &data) {
    RiderNode* temp(header);
    RiderNode* prev(nullptr);

    while(temp != nullptr && data.getPoints() <= temp->getData().getPoints()){
        prev = temp;
        temp = temp->getNext();
    }

    insertData(prev, data);
}



void RiderList::deleteData(RiderNode *riderNode) {
    RiderNode* temp(header);
    RiderNode* trail(nullptr);

    if(!isValidPos(riderNode)){
        if(errorMessage != nullptr){
            errorMessage->addErrorMessage("Rider not found\n");
        }
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

void RiderList::generatePositions() {
    RiderNode* temp(header);
    RiderNode* prev(nullptr);
    int i = 1;

    temp->getDataReference()->setPosition(i);
    prev = temp;
    temp = temp->getNext();

    while(temp != nullptr){
        if(prev->getData().getPoints() == temp->getData().getPoints()){
            temp->getDataReference()->setPosition(i);
        } else {
            i++;
            temp->getDataReference()->setPosition(i);
        }
        prev = temp;
        temp = temp->getNext();
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

RiderNode *RiderList::retrievePos(RiderManager &riderManager) {
    RiderNode* temp(header);
    RiderNode* last(getLastPos());

    if(temp == last){
        if(temp->getData() == riderManager){
            return temp;
        } else {
            if(errorMessage != nullptr){
                errorMessage->addErrorMessage("Rider with #" + riderManager.getRider().getNumber() + " was not found\n");
            }
            return nullptr;
        }
    } else {
        while(temp != nullptr){
            if(temp->getData() == riderManager){
                return temp;
            }
            temp = temp->getNext();
        }
    }

    if(errorMessage != nullptr){
        errorMessage->addErrorMessage("Rider with #" + riderManager.getRider().getNumber() + " was not found\n");
    }
    return nullptr;
}

RiderNode *RiderList::retrievePosIndex(int index) {
    RiderNode* temp(header);
    if(index > riderCount() || index < 0){
        return nullptr;
    }

    for(int i = 0; i < index; i++){
        temp = temp->getNext();
    }

    return temp;
}

RiderManager RiderList::retrieveData(RiderNode *riderNode) {
    RiderNode* temp(header);
    RiderNode* last(getLastPos());

    if(!isValidPos(riderNode)){
        if(errorMessage != nullptr){
            errorMessage->addErrorMessage("Error: rider not found\n");
        }
    }

    return riderNode->getData();
}

string RiderList::toString() {
    RiderNode* temp = header;
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

string RiderList::toStringIndexed(){
    RiderNode* temp = header;
    string result;
    int i = 1;

    if(isEmpty()){
        return "No riders in list";
    }

    while(temp != nullptr){
        result += temp->getData().toStringIndexed(i);
        result += "\n";
        temp = temp->getNext();
        i++;
    }

    return result;
}

void RiderList::deleteAll() {
    RiderNode* temp(header);
    RiderNode* trail(nullptr);
    RiderNode* last(getLastPos());

    if(temp == last){
        delete temp;
        header = nullptr;
    } else {
        while(temp != nullptr){
            trail = temp;
            temp = temp->getNext();
            delete trail;
        }
        delete temp;
        header = nullptr;
    }
}

void RiderList::writeToDisk(const string &fileName) {
    ofstream file(fileName);
    RiderNode* temp(header);
    string tempString;

    if(!file.is_open()){
        if(errorMessage != nullptr){
            errorMessage->addErrorMessage("Couldn't open " + fileName + "\n");
        }
        return;
    }
    while(temp != nullptr){
        tempString = temp->getData().toStringDisk();
        file << tempString << endl;
        temp = temp->getNext();
    }
    file.close();
}

RiderList *RiderList::copyFromDisk(const std::string &fileName) {
    ifstream file(fileName);
    RiderList* riderList = new RiderList(nullptr, errorMessage);
    string tempString;

    string firstName, lastName, country, team, number;
    int points;
    bool chosen;
    Rider tempRider;
    RiderManager tempRiderManager;

    deleteAll();

    if(!file.is_open()){
        if(errorMessage != nullptr){
            errorMessage->addErrorMessage("There was an error opening the rider data file\n");
            return new RiderList(nullptr, errorMessage);
        }
    }

    getline(file, tempString, '|');
    if(tempString.empty() || tempString == " "){
        return new RiderList(nullptr, errorMessage);
    }
    while(tempString != " " && !tempString.empty()){
        number = tempString;
        getline(file, tempString, '|');
        firstName = tempString;
        getline(file, tempString, '|');
        lastName = tempString;
        getline(file, tempString, '|');
        country = tempString;
        getline(file, tempString, '|');
        team = tempString;
        getline(file, tempString, '|');
        points = stoi(tempString);
        getline(file, tempString);
        tempRider.setData(firstName, lastName, number, country, team);
        tempRiderManager.setRider(tempRider);
        tempRiderManager.setPoints(points);
        riderList->insertOrdered(tempRiderManager);
        getline(file, tempString, '|');
    }

    riderList->generatePositions();

    return riderList;
}

void RiderList::modifyFromDisk(const string &fileName) {
    deleteAll();

    ifstream file(fileName);
    string tempString;

    string firstName, lastName, country, team, number;
    int points;
    bool chosen;
    Rider tempRider;
    RiderManager tempRiderEntry;

    getline(file, tempString, '|');
    if(tempString.empty() || tempString == " "){
        header = nullptr;
        return;
    }
    while(tempString != " " && !tempString.empty()){
        number = tempString;
        getline(file, tempString, '|');
        firstName = tempString;
        getline(file, tempString, '|');
        lastName = tempString;
        getline(file, tempString, '|');
        country = tempString;
        getline(file, tempString, '|');
        team = tempString;
        getline(file, tempString, '|');
        points = stoi(tempString);
        getline(file, tempString);
        tempRider.setData(firstName, lastName, number, country, team);
        tempRiderEntry.setRider(tempRider);
        tempRiderEntry.setPoints(points);
        insertOrdered(tempRiderEntry);
        getline(file, tempString, '|');
    }

    generatePositions();
}

//when this function is run, it generates a new list of the same elements,
//unlike operator= where it just copies the node references, basically the same list
RiderList &RiderList::deepCopy(RiderList *riderList){
    RiderNode *sourceHeader(riderList->getFirstPos());
    RiderNode *sourceFooter(riderList->getLastPos());

    deleteAll();

    if(!sourceHeader){
        this->header = nullptr;
        return *this;
    }

    if(sourceHeader == sourceFooter){
        this->header = new RiderNode(*(sourceHeader->getDataReference()));
        return *this;
    }

    header = new RiderNode(*(sourceHeader->getDataReference()));
    RiderNode* node = header;
    RiderNode* prev = new RiderNode();
    sourceHeader = sourceHeader->getNext();

    while(sourceHeader){
        RiderNode *newNode = new RiderNode(*(sourceHeader->getDataReference()));
        node->setNext(newNode);
        prev = node;
        node = node->getNext();
        node->setPrevious(prev);
        sourceHeader = sourceHeader->getNext();
    }

    if(riderList->errorMessage != nullptr){
        this->errorMessage = riderList->errorMessage;
    } else {
        this->errorMessage = nullptr;
    }

    return *this;
}

RiderList &RiderList::operator=(RiderList *riderList) {
    RiderNode *sourceHeader(riderList->getFirstPos());
    RiderNode *sourceFooter(riderList->getLastPos());

    deleteAll();

    if(!sourceHeader){
        this->header = nullptr;
        return *this;
    }

    if(sourceHeader == sourceFooter){
        this->header = sourceHeader;
        return *this;
    }

    RiderNode* node = header;
    RiderNode* prev;
    sourceHeader = sourceHeader->getNext();

    while(sourceHeader != nullptr){
        prev = node;
        node->setNext(sourceHeader);
        node = node->getNext();
        node->setPrevious(prev);
        sourceHeader = sourceHeader->getNext();
    }

    if(riderList->errorMessage){
        this->errorMessage = riderList->errorMessage;
    } else {
        this->errorMessage = nullptr;
    }

    return *this;
}

vector<RiderManager> RiderList::copyToVector(){
    RiderNode* node = header;
    vector<RiderManager> result;
    RiderManager tempRiderManager;

    while(node != nullptr){
        tempRiderManager = RiderManager();
        tempRiderManager = node->getData();
        result.push_back(tempRiderManager);
        node = node->getNext();
    }

    return result;
}
