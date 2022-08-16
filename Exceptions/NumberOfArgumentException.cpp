#include <exception>
#include <string.h>
using namespace std;
//
// Created by Lenovo on 8/13/2022.
//
#include "Exceptions.h"
char * NumberOfArgumentException::what() {
    return "You entered incorrect number of argument for help enter -help";
}

ValidationErrorException::ValidationErrorException(char *msg) {
    message = msg;
}
//TODO: strupper implement
char *ValidationErrorException::what() {
    return message;
}
