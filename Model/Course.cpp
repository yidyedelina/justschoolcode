//
// Created by Lenovo on 8/12/2022.
//

#include "Course.h"
#include "../utility_functions.h"

const string &Course::getId() const {
    return Id;
}

const string &Course::getName() const {
    return Name;
}

int Course::getCreditHour() const {
    return creditHour;
}

const string &Course::getDepartment() const {
    return department;
}

int Course::getSemester(){
    return semester;
}

int Course::getYear() {
    return year;
}

string Course::toString() {
    return Id + "," + Name + "," + to_string(creditHour) + "," + department + "," + to_string(semester) + "," + to_string(year);
}

Course::Course(string id) {
    vector<string*> data = loadData("../data/CourseList.csv",6);
    for(auto cr : data)
    {
        Course course(cr);
        if(course.getId() == id)
        {
            this->Id = course.getId();
            this->Name = course.getName();
            this->creditHour = course.getCreditHour();
            this->department = course.getDepartment();
            this->semester = course.getSemester();
            this->year = course.getYear();
        }
    }
}

Course::Course(string *fields) {
    this->Id = fields[0];
    this->Name = fields[1];
    this->creditHour = stoi(fields[2]);
    this->department = fields[3];
    this->semester = stoi(fields[4]);
    this->year = stoi(fields[5]);

}
