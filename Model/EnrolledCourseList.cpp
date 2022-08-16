//
// Created by Lenovo on 8/12/2022.
//

#include <iostream>
#include "EnrolledCourseList.h"
#include "../utility_functions.h"
#include "Course.h"
#include "../Exceptions/Exceptions.h"

EnrolledCourseList::EnrolledCourseList(string studentId, int year, int semester) {
    vector<string*> data = loadData("../data/EnrolledCourseList.csv",4);
    for(auto row : data){
        EnrolledCourse enrolledCourse(row);
        Course course(enrolledCourse.getCourseCode());
        if(enrolledCourse.getStudentId() == studentId && course.getYear() == year && course.getSemester() == semester){
            this->enrolledCourseList.push_back(enrolledCourse);
        }
        this->enrolledCourseMap[studentId] = enrolledCourseList;
    }
    courseListRef = new CourseList();
}
string EnrolledCourseList::MarkToLetterGrade(float mark) {
    if (mark >= 90)
        return "A+";
    else if (mark >= 85)
        return "A";
    else if (mark >= 80)
        return "A-";
    else if (mark >= 75)
        return "B+";
    else if (mark >= 70)
        return "B";
    else if (mark >= 65)
        return "B-";
    else if (mark >= 60)
        return "C+";
    else if (mark >= 50)
        return "C";
    else if (mark >= 45)
        return "C-";
    else if (mark >= 40)
        return "D";
    return "F";
}
unordered_map<string, float> grade_reference = {{"A+", 4}, {"A", 4}, {"A-", 3.75}, {"B+", 3.5}, {"B", 3}, {"B-", 2.75}, {"C+", 2.5}, {"C", 2}, {"C-", 1.75}, {"D", 1}, {"F", 0}};

double EnrolledCourseList::CalculateGpa() {
    double total_credit_hour = 0;
    double total_mark = 0;
    for(auto enrolledCourse : this->enrolledCourseList){
        Course course(enrolledCourse.getCourseCode());
        total_credit_hour += course.getCreditHour();
        total_mark += grade_reference[MarkToLetterGrade(enrolledCourse.getGrade())] * course.getCreditHour();
    }
    return total_mark / total_credit_hour;
}

vector<EnrolledCourse> EnrolledCourseList::getEnrolledCourseList() {
    return this->enrolledCourseList;
}
unordered_map<string, vector<EnrolledCourse>>* EnrolledCourseList::getEnrolledCourseMap() {
    return &this->enrolledCourseMap;
}

EnrolledCourse EnrolledCourseList::getEnrolledCourse(string id) {
    for(auto course: enrolledCourseList){
        if(course.getCourseCode() == id){
           return course;
        }
    }
    string* p = {};
    EnrolledCourse empty(p);
    return empty;
}

EnrolledCourseList::EnrolledCourseList() {
    vector<string*> data = loadData("../data/EnrolledCourseList.csv",4);
    for(auto row : data){
        EnrolledCourse enrolledCourse(row);
        string name = enrolledCourse.getStudentId();
        this->enrolledCourseList.push_back(enrolledCourse);
        if(enrolledCourseMap.find(name) == enrolledCourseMap.end()){
            vector<EnrolledCourse> s = {enrolledCourse};
            enrolledCourseMap[name] = s;
        }else{
            enrolledCourseMap[name].push_back(enrolledCourse);
        }

    }
    courseListRef = new CourseList;
}

vector<EnrolledCourse> EnrolledCourseList::filterEnrolledCourseList(string studentId, int year, int semester) {
    vector<EnrolledCourse> filteredEnrolledCourse;
    for(auto enroll : enrolledCourseList){
        Course cr = courseListRef->getCourse(enroll.getCourseCode());
        if(enroll.getStudentId() == studentId && cr.getYear() == year && cr.getSemester() == semester){
            filteredEnrolledCourse.push_back(enroll);
        }
    }
    return filteredEnrolledCourse;
}


