//
// Created by Lenovo on 8/13/2022.
//

#ifndef LEARNING_MANAGEMENT_SYSTEM_EXCEPTIONS_H
#define LEARNING_MANAGEMENT_SYSTEM_EXCEPTIONS_H

#include <exception>

class NumberOfArgumentException : public std::exception {

public:
    char* what();
};
class ValidationErrorException : public std::exception {
private: char * message;
public:
    ValidationErrorException(char * msg);
    char * what();
};

#endif //LEARNING_MANAGEMENT_SYSTEM_EXCEPTIONS_H
