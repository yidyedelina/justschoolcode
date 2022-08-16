//
// Created by Lenovo on 8/12/2022.
//

#ifndef LEARNING_MANAGEMENT_SYSTEM_VIEWS_H
#define LEARNING_MANAGEMENT_SYSTEM_VIEWS_H


#include "../Services/LearningManagementService.h"

class Views {
public:
    Views();
    void homePage();
    void studentMarkPage();

    void printString(int number, char s) const;

    void seeSectionScore(vector<StudentMark> studentMark);

    void seeStudentScore(StudentMark* studentMark);
};


#endif //LEARNING_MANAGEMENT_SYSTEM_VIEWS_H
