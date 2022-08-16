//
// Created by Lenovo on 8/12/2022.
//

#include <cmath>
#include "EnrolledCourse.h"

const string &EnrolledCourse::getCourseCode() const {
    return courseCode;
}

const string &EnrolledCourse::getStudentId() const {
    return studentId;
}

float EnrolledCourse::getGrade() {
    return grade;
}

Status EnrolledCourse::getStatus() const {
    return status;
}

string EnrolledCourse::toString() {
    int roundedGrade;
    if(grade - floor(grade) < 0.5){
        roundedGrade = floor(grade);
    }else roundedGrade = ceil(grade);
    string changed = courseCode + "," + studentId + "," + to_string(roundedGrade) + "," + to_string(status);
    return changed;
}

EnrolledCourse::EnrolledCourse(string *fields) {
    courseCode = fields[0];
    studentId = fields[1];
    grade = stof(fields[2]);
    status = static_cast<Status>(stoi(fields[3]));
}

void EnrolledCourse::setGrade(double d) {
    grade = d;
}

void EnrolledCourse::setStatus(int i) {
    status = static_cast<Status>(i);
}

EnrolledCourse::EnrolledCourse(string cr_code, string id, float gr, int st) {
    this->courseCode = cr_code;
    this->studentId = id;
    this->grade = gr;
    this->status = static_cast<Status> (st);
}
