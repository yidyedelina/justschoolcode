//
// Created by Lenovo on 8/12/2022.
//

#ifndef LEARNING_MANAGEMENT_SYSTEM_ENROLLEDCOURSE_H
#define LEARNING_MANAGEMENT_SYSTEM_ENROLLEDCOURSE_H
#include <string>
using namespace std;
enum Status {
    NOT_GRADED,
    GRADED,
    APPROVED,
};
class EnrolledCourse {
    string courseCode;
    string studentId;
    float grade;
    Status status = NOT_GRADED;
public:
    EnrolledCourse(string* fields);
    EnrolledCourse(string cr_code, string id, float grade, int st);
    const string &getCourseCode() const;
    const string &getStudentId() const;
    float getGrade();
    Status getStatus() const;
    string toString();

    void setGrade(double d);

    void setStatus(int i);
};


#endif //LEARNING_MANAGEMENT_SYSTEM_ENROLLEDCOURSE_H
