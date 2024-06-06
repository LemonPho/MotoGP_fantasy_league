#include "error-message.h"
#include <utility>

using namespace std;

ErrorMessage::ErrorMessage() {
    message = "";
}

void ErrorMessage::setErrorMessage(string errorMessage) {
    message = std::move(errorMessage);
}

void ErrorMessage::addErrorMessage(const string& errorMessage) {
    if(isEmpty()){
        message = errorMessage;
    } else {
        message += errorMessage;
    }
}

string ErrorMessage::getErrorMessage() {
    //after displaying the message is automatically deleted
    string tempMessage = message;
    message = "";
    return tempMessage;
}

bool ErrorMessage::isEmpty() {
    return message.empty();
}