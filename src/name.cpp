#include "name.h"

Name::Name() {
    firstName = "FIRST_NAME";
    lastName = "LAST_NAME";
}

void Name::setData(string &fn, string &ln) {
    firstName = fn;
    lastName = ln;
}

string Name::getFirstName() {
    return firstName;
}

string Name::getLastName() {
    return lastName;
}

string Name::getName(){
    return firstName + " " + lastName;
}

string Name::toString() {
    string result;
    unsigned int spaces = 1;

    spaces += firstName.length() + lastName.length();
    if(spaces < SPACE_NAME){
        result = fillSpaces(getName(), SPACE_NAME-spaces);
    } else {
        result = getName();
    }

    return result;
}
