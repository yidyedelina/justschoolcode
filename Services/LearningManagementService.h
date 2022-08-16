//
// Created by Lenovo on 8/12/2022.
//

#ifndef LEARNING_MANAGEMENT_SYSTEM_LEARNINGMANAGEMENTSERVICE_H
#define LEARNING_MANAGEMENT_SYSTEM_LEARNINGMANAGEMENTSERVICE_H


#include "../Model/StudentList.h"
#include "../Model/CourseList.h"
#include "../Model/EnrolledCourseList.h"
struct Grade {
    string subjectName;
    float mark;
    int creditHour;
};
struct StudentMark {
    string name;
    double gpa;
    vector<Grade> grades;
};
struct {
    bool operator()(StudentMark a, StudentMark b) const { return a.gpa < b.gpa;}
} lessGpa;
struct {
    bool operator()(StudentMark a, StudentMark b) const { return a.gpa > b.gpa;}
} greatGpa;
class LearningManagementService {
public:
    LearningManagementService();
    vector<StudentMark> getStudentsMark(string department, string section,int join_year,int year, int semester);
    vector<StudentMark> MarkCommand(vector<string> parsedData);
    StudentMark getStudentMark(string studentId, int year, int semester);
    void RegisterCommand(vector<string> parsedData);
    void SearchCommand(string id);
    void EditCommand(vector<string> parsedData);

    void AddGradeCommand(vector<string> vector1);

    vector<StudentMark> FilterCommand(vector<string> parsedData);

    StudentMark CGPA(string id);
    void generateStudentEnrolledData();

    vector<StudentMark> ListCommand(vector<string> parsedInput);

private:
    StudentList* studentListRef;
    EnrolledCourseList* enrolledCourseListRef;
    CourseList* courseListRef;
    int current_year = 2014;
    int current_semester = 2;
    vector<string> departments = {
            "software_engineering", "electrical_engineering", "electromechanical_engineering"
    };
    StudentMark getStudentMark(string);

    int validateId(string Id);

    void validateDepartment(string dep);

    void validateGrade(double grade);


    void cumulative_display(string &id);

    void listCourse(vector<Course> courseList);

    double CalculateGpa(vector<EnrolledCourse> enrolledCourseList);
};


#endif //LEARNING_MANAGEMENT_SYSTEM_LEARNINGMANAGEMENTSERVICE_H
