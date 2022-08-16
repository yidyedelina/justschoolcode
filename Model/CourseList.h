//
// Created by Lenovo on 8/12/2022.
//

#ifndef LEARNING_MANAGEMENT_SYSTEM_COURSELIST_H
#define LEARNING_MANAGEMENT_SYSTEM_COURSELIST_H


#include "Course.h"
#include <vector>
#include <string>
using namespace std;
class CourseList {
    vector<Course> courseList;
public:
    CourseList(string department, int year, int semester);
    CourseList();
    void addCourse(Course course);
    void removeCourse(string id);
    void updateCourse(Course course);
    Course getCourse(string id);
    vector<Course> getCourseList();
};


#endif //LEARNING_MANAGEMENT_SYSTEM_COURSELIST_H
