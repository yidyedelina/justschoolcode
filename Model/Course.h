//
// Created by Lenovo on 8/12/2022.
//

#ifndef LEARNING_MANAGEMENT_SYSTEM_COURSE_H
#define LEARNING_MANAGEMENT_SYSTEM_COURSE_H
#include <string>
using namespace std;

class Course {
    string Id;
    string Name;
    int creditHour;
    string department;
public:
    Course(string* fields);
    Course(string id);
    const string &getId() const;

    const string &getName() const;

    int getCreditHour() const;

    const string &getDepartment() const;

    int getSemester();

    int getYear();
    string toString();

private:
    int semester;
    int year;
};


#endif //LEARNING_MANAGEMENT_SYSTEM_COURSE_H
