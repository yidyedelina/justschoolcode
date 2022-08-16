//
// Created by Lenovo on 8/12/2022.
//

#ifndef LEARNING_MANAGEMENT_SYSTEM_ENROLLEDCOURSELIST_H
#define LEARNING_MANAGEMENT_SYSTEM_ENROLLEDCOURSELIST_H
#include <vector>
#include "EnrolledCourse.h"
#include "CourseList.h"
#include <string>
#include <unordered_map>

class EnrolledCourseList {
    vector<EnrolledCourse> enrolledCourseList;
    unordered_map<string,vector<EnrolledCourse>> enrolledCourseMap{};
    CourseList* courseListRef;
public:
    EnrolledCourseList(string studentId, int year, int semester);
    EnrolledCourseList();
    vector<EnrolledCourse> filterEnrolledCourseList(string studentId, int year, int semester);
    static string MarkToLetterGrade(float grade);
    double CalculateGpa();
    void addEnrolledCourse(EnrolledCourse enrolledCourse);
    void removeEnrolledCourse(string id);
    void updateEnrolledCourse(EnrolledCourse enrolledCourse);
    EnrolledCourse getEnrolledCourse(string id);
    vector<EnrolledCourse> getEnrolledCourseList();

    unordered_map<string, vector<EnrolledCourse>>* getEnrolledCourseMap();
};


#endif //LEARNING_MANAGEMENT_SYSTEM_ENROLLEDCOURSELIST_H
