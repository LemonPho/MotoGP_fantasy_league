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

MemberList::MemberList() : header(nullptr), errorMessage(){}

MemberList::MemberList(ErrorMessage *errorMessage) {
    this->header = nullptr;
    this->errorMessage = errorMessage;
}

MemberList::MemberList(MemberNode* header, ErrorMessage *errorMessage){
    this->header = header;
    this->errorMessage = errorMessage;
}

MemberList::~MemberList() {
    deleteAll();
    delete header;
}

void MemberList::setErrorMessage(ErrorMessage *errorMessage) {
    this->errorMessage = errorMessage;
}

bool MemberList::isEmpty() {
    return header == nullptr;
}

void MemberList::insertData(MemberNode *memberNode, const Member &data) {
    if(memberNode != nullptr && !isValidPos(memberNode)){
        if(errorMessage != nullptr){
            errorMessage->addErrorMessage("Invalid position when inserting member, try again after restart\n");
        }
        throw exception();
    }

    if(memberNode == nullptr){
        memberNode = header;
    }

    MemberNode* toInsert(new MemberNode(data));

    if(toInsert == nullptr){
        if(errorMessage != nullptr){
            errorMessage->addErrorMessage("No more space found for program, maybe out of system ram\n");
        }
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
        if(errorMessage != nullptr){
            errorMessage->addErrorMessage("Error when deleting, member doesn't exist\n");
        }
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

MemberNode *MemberList::retrievePos(const Member &data) {
    MemberNode* temp(header);

    while(temp != nullptr){
        if(temp->getData() == data){
            return temp;
        }
        temp = temp->getNext();
    }
    return nullptr;
}

void MemberList::retrieveMemberPicks(RiderList *riderList) {
    if(isEmpty()){
        return;
    }

    MemberNode* tempMemberNode(header);
    Member tempMember;
    RiderManager tempRookie;
    RiderManager riderEntry;
    Rider rider;
    string tempNumber;
    int tempMemberPoints=0;


    //complete the rider lists and rookies of each member, because readFromDisk only assigns riders with only their numbers
    while(tempMemberNode != nullptr){
        //retrieve rookie number and get full rookie data to assign
        tempMember = tempMemberNode->getData();
        tempMemberPoints = 0;
        //node to go through member rider list
        RiderNode* tempRiderNode1(tempMember.getRiderList()->getFirstPos());
        while(tempRiderNode1 != nullptr){
            //get full data of each rider, same method as rookie
            RiderNode* tempRiderNode2;
            tempNumber = tempRiderNode1->getData().getRider().getNumber();
            rider.setNumber(tempNumber);
            riderEntry.setRider(rider);
            tempRiderNode2 = riderList->retrievePos(riderEntry);
            if(tempRiderNode2 == nullptr){
                if(errorMessage != nullptr){
                    string tempMessage = "Rider #" + tempNumber + " from " + tempMember.getUserName() + " picks not found\n";
                    errorMessage->addErrorMessage(tempMessage);
                }
            } else {
                riderEntry = tempRiderNode2->getData();
                tempMemberPoints += riderEntry.getPoints();
                tempRiderNode1->setData(riderEntry);
                tempRiderNode1 = tempRiderNode1->getNext();
            }
        }
        tempMember.setPoints(tempMemberPoints);
        tempMemberNode->setData(tempMember);
        tempMemberNode = tempMemberNode->getNext();
    }
}

void MemberList::updateMembersPoints() {
    int totalPoints;
    MemberNode* tempMemberNode(header);
    Member tempMember;
    Rider tempRookie;
    RiderNode* tempRiderNode = new RiderNode();

    while(tempMemberNode != nullptr){
        totalPoints = 0;
        tempMember = tempMemberNode->getData();
        tempRiderNode = tempMember.getRiderList()->getFirstPos();
        while(tempRiderNode != nullptr) {
            totalPoints += tempRiderNode->getData().getPoints();
            tempRiderNode = tempRiderNode->getNext();
        }
        tempMember.setPoints(totalPoints);
        tempMemberNode->setData(tempMember);
        tempMemberNode = tempMemberNode->getNext();
    }
}

void MemberList::updateMembersRiders(RiderList* riderList) {
    float totalPoints;
    MemberNode* tempMemberNode(header);
    RiderManager tempRiderManager;
    Rider tempRider;
    Member tempMember;
    RiderNode* tempRiderNode1;
    RiderNode* tempRiderNode2;

    while(tempMemberNode != nullptr){
        totalPoints = 0;
        tempMember = tempMemberNode->getData();
        tempRiderNode1 = tempMember.getRiderList()->getFirstPos();
        while(tempRiderNode1 != nullptr){
            tempRiderManager = tempRiderNode1->getData();
            tempRiderNode2 = riderList->getFirstPos();
            while(tempRiderNode2 != nullptr){
                if(tempRiderNode2->getData() == tempRiderManager){
                    tempRiderManager = tempRiderNode2->getData();
                    break;
                }
                tempRiderNode2 = tempRiderNode2->getNext();
            }
            tempRiderNode1->setData(tempRiderManager);
            totalPoints += tempRiderNode1->getData().getPoints();
            tempRiderNode1 = tempRiderNode1->getNext();
        }
        totalPoints += tempMember.getPoints();
        tempMember.setPoints(totalPoints);
        tempMemberNode->setData(tempMember);
        tempMemberNode = tempMemberNode->getNext();
    }
}

string MemberList::addExtraMembersPoints(RiderList *riderList) {
    string result = "<table>";
    int positionCounter = 1;

    float totalPoints = 0;
    float pointsMultiplier[] = {0.1, 0.07, 0.05, 0.0325, 0.02};
    int i;
    MemberNode* tempMemberNode(header);
    Member tempMember;
    RiderNode* tempRiderNode1 = new RiderNode();
    RiderNode* tempRiderNode2 = riderList->getFirstPos();
    RiderManager tempRiderManager1;
    RiderManager tempRiderManager2;
    Rider rider;

    std::ostringstream stream;

    while(tempMemberNode != nullptr){
        tempMember = tempMemberNode->getData();
        totalPoints = tempMember.getPoints();
        tempRiderNode1 = tempMember.getRiderList()->getFirstPos();
        tempRiderNode2 = riderList->getFirstPos();
        i=0;

        result += "<tr>";
        result += "<td>";
        result += "<b>";
        result += to_string(positionCounter);
        result += ". ";
        result += tempMember.getUserName();
        result += " - ";

        while(tempRiderNode1 != nullptr){
            tempRiderManager2 = tempRiderNode2->getData();
            tempRiderManager1 = tempRiderNode1->getData();

            if(tempRiderManager1 == tempRiderManager2){
                totalPoints += pointsMultiplier[i] * tempRiderManager2.getPoints();
            }

            tempRiderNode1 = tempRiderNode1->getNext();
            tempRiderNode2 = tempRiderNode2->getNext();
        }

        stream << fixed << setprecision(2) << totalPoints;
        result += stream.str();

        tempRiderNode1 = tempMember.getRiderList()->getFirstPos();
        tempRiderNode2 = riderList->getFirstPos();

        while(tempRiderNode1 != nullptr){
            stream.str("");
            stream.clear();
            tempRiderManager2 = tempRiderNode2->getData();
            tempRiderManager1 = tempRiderNode1->getData();
            rider = tempRiderManager2.getRider();
            if(tempRiderManager1 == tempRiderManager2){
                totalPoints += pointsMultiplier[i] * tempRiderManager2.getPoints();
                result += "<td>";
                result += rider.getFirstName()[0];
                result += ". ";
                for(int i = 0; i < 3; i++){
                    result += rider.getLastName()[i];
                }
                result += " - ";
                stream << std::fixed << std::setprecision(2) << (pointsMultiplier[i] * tempRiderManager2.getPoints()) + tempRiderManager2.getPoints();
                result += stream.str();

                result += "</td>";
                
            } else {
                result += "<td>";
                result += rider.getFirstName()[0];
                result += ". ";
                for (int i = 0; i < 3; i++) {
                    result += rider.getLastName()[i];
                }
                result += " - ";
                stream << std::fixed << std::setprecision(2) << tempRiderManager2.getPoints();
                result += stream.str();

                result += "</td>";
            }
            tempRiderNode1 = tempRiderNode1->getNext();
            tempRiderNode2 = tempRiderNode2->getNext();
            i++;
        }
        tempMember.setPoints(totalPoints);
        tempMemberNode->setData(tempMember);
        tempMemberNode = tempMemberNode->getNext();
    }

    result += "</table>";

    return result;
}

void MemberList::sortMembers(RiderNode* riderHead) {
    header = mergeSort(header, riderHead);
}

MemberNode *MemberList::split(MemberNode *head) {
    MemberNode *fast = head, *slow = head;
    while(fast->getNext() && fast->getNext()->getNext()){
        fast = fast->getNext()->getNext();
        slow = slow->getNext();
    }
    MemberNode* temp = slow->getNext();
    slow->setNext(nullptr);
    return temp;
}

MemberNode *MemberList::tieBreaker(MemberNode *firstMember, MemberNode *secondMember, RiderNode *riderHead) {
    //rider picks of each player (first, second)
    RiderNode* firstPicks = firstMember->getDataReference()->getRiderList()->getFirstPos();
    RiderNode* secondPicks = secondMember->getDataReference()->getRiderList()->getFirstPos();
    RiderNode* tempRider = riderHead;
    bool samePicks = true;
    int i = 1;

    //if one of the members have one of the top 5 riders correctly guessed, the one that chose correctly will be ahead
    //the if's are structured so that if they both have the same rider in the same position, then it keeps checking
    while(firstPicks != nullptr && secondPicks != nullptr){
        if(firstPicks == tempRider && secondPicks != tempRider){
            firstMember->setNext(merge(firstMember->getNext(), secondMember, riderHead));
            firstMember->getNext()->setPrevious(firstMember);
            firstMember->setPrevious(nullptr);
            return firstMember;
        } else if(firstPicks != tempRider && secondPicks == tempRider){
            secondMember->setNext(merge(firstMember, secondMember->getNext(), riderHead));
            secondMember->getNext()->setPrevious(secondMember);
            secondMember->setPrevious(nullptr);
            return secondMember;
        }

        firstPicks = firstPicks->getNext();
        secondPicks = secondPicks->getNext();
        tempRider = tempRider->getNext();
    }

    firstPicks = firstMember->getDataReference()->getRiderList()->getFirstPos();
    secondPicks = secondMember->getDataReference()->getRiderList()->getFirstPos();
    //check to see if one of the members has a rider in the correct position
    //only goes to getNext to not lcheck the independant rider, as they would be read as 6th position instead of idnependant
    while(secondPicks->getNext() != nullptr && firstPicks->getNext() != nullptr){
        if(secondPicks->getData().getPosition() != firstPicks->getData().getPosition()){
            if(secondPicks->getData().getPosition() == i){
                secondMember->setNext(merge(firstMember, secondMember->getNext(), riderHead));
                secondMember->getNext()->setPrevious(secondMember);
                secondMember->setPrevious(nullptr);
                return secondMember;
            } else if(firstPicks->getData().getPosition() == i){
                firstMember->setNext(merge(firstMember->getNext(), secondMember, riderHead));
                firstMember->getNext()->setPrevious(firstMember);
                firstMember->setPrevious(nullptr);
                return firstMember;
            }
        }

        i++;
        firstPicks = firstPicks->getNext();
        secondPicks = secondPicks->getNext();
    }

    firstPicks = firstMember->getDataReference()->getRiderList()->getFirstPos();
    secondPicks = secondMember->getDataReference()->getRiderList()->getFirstPos();
    //iterate until points are not the same
    while((firstPicks->getData().getPoints() == secondPicks->getData().getPoints()) && (firstPicks->getNext() != nullptr && firstPicks->getNext() != nullptr)){
        firstPicks = firstPicks->getNext();
        secondPicks = secondPicks->getNext();
        if(secondPicks->getData() != firstPicks->getData()){
            samePicks = false;
        }
    }

    if(secondPicks->getData() != firstPicks->getData()){
        samePicks = false;
    }

    if(samePicks){
        if(errorMessage != nullptr){
            errorMessage->addErrorMessage(firstMember->getData().getUserName() + " and " + secondMember->getData().getUserName() + " have the same rider picks!\n");
        }
    }

    //conditionals to find which player has a rider with more points
    if(firstPicks->getData().getPoints() > secondPicks->getData().getPoints()){
        firstMember->setNext(merge(firstMember->getNext(), secondMember, riderHead));
        firstMember->getNext()->setPrevious(firstMember);
        firstMember->setPrevious(nullptr);
        return firstMember;
    } else {
        secondMember->setNext(merge(firstMember, secondMember->getNext(), riderHead));
        secondMember->getNext()->setPrevious(secondMember);
        secondMember->setPrevious(nullptr);
        return secondMember;
    }
}

MemberNode *MemberList::merge(MemberNode *first, MemberNode *second, RiderNode* riderHead) {
    if(!first){
        return second;
    }

    if(!second){
        return first;
    }

    //both players have the same amount of points, tiebreaker
    if(first->getData().getPoints() == second->getData().getPoints()){
        MemberNode* temp = tieBreaker(first, second, riderHead);
        return temp;
    } else if(first->getData().getPoints() > second->getData().getPoints()){
        first->setNext(merge(first->getNext(), second, riderHead));
        first->getNext()->setPrevious(first);
        first->setPrevious(nullptr);
        return first;
    } else {
        second->setNext(merge(first, second->getNext(), riderHead));
        second->getNext()->setPrevious(second);
        second->setPrevious(nullptr);
        return second;
    }
}

MemberNode *MemberList::mergeSort(MemberNode *head, RiderNode* riderHead) {
    if(!head || !head->getNext()){
        return head;
    }
    MemberNode* second = split(head);

    head = mergeSort(head, riderHead);
    second = mergeSort(second, riderHead);

    return merge(head, second, riderHead);
}

string MemberList::toString() {
    MemberNode* temp(header);
    MemberNode* last(getLastPos());
    Member tempMember;
    string result;

    while(temp != nullptr){
        tempMember = temp->getData();
        result += tempMember.toStringSmall();
        if(temp != last) {
            result += "\n";
        }
        temp = temp->getNext();
    }

    return result;
}

string MemberList::toStringSmallHTML() {
    //currently this is used to save as a html table with html tags
    MemberNode* tempMemberNode(header);
    RiderNode* tempRiderNode = new RiderNode();
    Member tempMember;
    RiderManager tempRiderManager;
    string result = "";

    int i = 1;
    result += "<table>";
    while(tempMemberNode != nullptr){
        std::ostringstream stream;
        tempMember = tempMemberNode->getData();
        result += "<tr>";
        result += "<td>";
        result += "<b>";
        result += to_string(i);
        result += ". ";
        result += tempMember.getUserName();
        result += " - ";
        stream << std::fixed << std::setprecision(2) << tempMember.getPoints();
        result += stream.str();
        result += "</b>";
        result += "</td>";
        tempRiderNode = tempMember.getRiderList()->getFirstPos();
        while(tempRiderNode != nullptr){
            tempRiderManager = tempRiderNode->getData();
            result += "<td>";
            result += tempRiderManager.toStringSmall(false);
            tempRiderNode = tempRiderNode->getNext();
            result += "</td>";
        }
        result += "</tr>\n";
        tempMemberNode = tempMemberNode->getNext();
        i++;
    }
    result += "</table>";

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

//should create a toStringDisk function
void MemberList::writeToDisk(const string &fileName) {
    ofstream file(fileName, ios::out);
    MemberNode* temp(header);
    string tempString;

    if(!file.is_open()){
        if(errorMessage != nullptr){
            errorMessage->addErrorMessage("Couldn't open " + fileName + "\n");
        }
        return;
    }
    while(temp != nullptr){
        RiderNode* tempRiderNode(temp->getData().getRiderList()->getFirstPos());
        tempString = temp->getData().getUserName();
        tempString += "|";
        while(tempRiderNode != nullptr) {
            tempString += tempRiderNode->getData().getRider().getNumber();
            tempString += "|";
            tempRiderNode = tempRiderNode->getNext();
        }
        file << tempString << endl;
        temp = temp->getNext();
    }
    file.close();
}

MemberList *MemberList::copyFromDisk(const string &fileName) {
    ifstream file(fileName);
    MemberList *memberList = new MemberList(errorMessage);
    string tempString;

    string userName, rookieNumber;
    Rider tempRider;
    RiderManager tempRiderManager;
    int pointsMember=0;
    Member tempMember;

    string number;

    getline(file, tempString, '|');
    if(tempString.empty() || tempString == " " || tempString == "/n"){
        return new MemberList(errorMessage);
    }
    while(tempString != " " && !tempString.empty()){
        int i;
        userName = tempString;
        for(i = 0; i < RIDER_COUNT; i++){
            getline(file, tempString, '|');
            number = tempString;
            tempRider.setNumber(number);
            tempRiderManager.setRider(tempRider);
            tempMember.insertRider(tempRiderManager);
        }
        tempMember.setUserName(userName);
        tempMember.setPoints(pointsMember);
        memberList->insertData(memberList->getFirstPos(), tempMember);
        getline(file, tempString);
        getline(file, tempString, '|');
        tempMember = Member();
    }
    return memberList;
}

void MemberList::modifyFromDisk(const std::string &fileName) {
    ifstream file(fileName);
    string tempString;

    string userName, rookieNumber;
    Rider tempRider;
    RiderManager tempRiderManager;
    int pointsMember=0;
    Member tempMember;
    string number;

    deleteAll();

    getline(file, tempString, '|');
    if(tempString.empty() || tempString == " " || tempString == "/n"){
        header = nullptr;
        return;
    }

    while(tempString != " " && !tempString.empty()){
        int i;
        userName = tempString;
        for(i = 0; i < RIDER_COUNT; i++){
            getline(file, tempString, '|');
            number = tempString;
            tempRider.setNumber(number);
            tempRiderManager.setRider(tempRider);
            tempMember.insertRider(tempRiderManager);
        }
        tempMember.setUserName(userName);
        tempMember.setPoints(pointsMember);
        insertData(header, tempMember);
        getline(file, tempString);
        getline(file, tempString, '|');
        tempMember = Member();
    }
}

MemberList& MemberList::deepCopy(MemberList *memberList) {
    MemberNode *sourceHeader(memberList->getFirstPos());
    MemberNode *sourceFooter(memberList->getLastPos());

    deleteAll();

    if(!sourceHeader){
        this->header = nullptr;
        return *this;
    }

    if(sourceHeader == sourceFooter){
        this->header = new MemberNode(*(sourceHeader->getDataReference()));
        return *this;
    }

    header = new MemberNode(*(sourceHeader->getDataReference()));
    MemberNode* node = header;
    MemberNode* prev = new MemberNode();
    sourceHeader = sourceHeader->getNext();

    while(sourceHeader){
        MemberNode *newNode = new MemberNode(*(sourceHeader->getDataReference()));
        node->setNext(newNode);
        prev = node;
        node = node->getNext();
        node->setPrevious(prev);
        sourceHeader = sourceHeader->getNext();
    }

    if(memberList->errorMessage != nullptr){
        this->errorMessage = memberList->errorMessage;
    } else {
        this->errorMessage = nullptr;
    }

    return *this;
}

MemberList& MemberList::operator=(MemberList *memberList) {
    MemberNode *sourceHeader(memberList->getFirstPos());
    MemberNode *sourceFooter(memberList->getLastPos());

    deleteAll();

    if(!sourceHeader){
        this->header = nullptr;
        return *this;
    }

    if(sourceHeader == sourceFooter){
        this->header = sourceHeader;
        return *this;
    }

    MemberNode* node = header;
    MemberNode* prev;
    sourceHeader = sourceHeader->getNext();

    while(sourceHeader != nullptr){
        prev = node;
        node->setNext(sourceHeader);
        node = node->getNext();
        node->setPrevious(prev);
        sourceHeader = sourceHeader->getNext();
    }

    if(memberList->errorMessage){
        this->errorMessage = memberList->errorMessage;
    } else {
        this->errorMessage = nullptr;
    }

    return *this;
}
