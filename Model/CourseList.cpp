//
// Created by Lenovo on 8/12/2022.
//

#include <iostream>
#include "CourseList.h"
#include "../utility_functions.h"

CourseList::CourseList(string department, int year, int semester) {
    vector<string*> data = loadData("../data/CourseList.csv",6);
    for(auto row : data){
        Course course(row);
        if(course.getDepartment() == department && course.getYear() == year && course.getSemester() == semester){
            this->courseList.push_back(course);
        }
    }

}

vector<Course> CourseList::getCourseList() {
    return this->courseList;
}
vector<Course> CourseList::getCourseList(string department, int year, int semester) {
    vector<Course> courseLi;
    for(auto course:courseList){
        if(course.getYear() == year && course.getSemester() == semester) {
            courseLi.push_back(course);
        }
    }
    return courseLi;
}
CourseList::CourseList() {
    vector<string*> data = loadData("../data/CourseList.csv",6);
    for(auto row : data){
        Course course(row);
        this->courseList.push_back(course);
    }
}

Course CourseList::getCourse(string id) {
    for(auto course: courseList){
        if(course.getId() == id){
           return course;
        }
    }
    Course cr("ets2321");
    return cr;
}
