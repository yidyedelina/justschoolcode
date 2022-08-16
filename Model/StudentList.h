//
// Created by Lenovo on 8/12/2022.
//

#ifndef LEARNING_MANAGEMENT_SYSTEM_STUDENTLIST_H
#define LEARNING_MANAGEMENT_SYSTEM_STUDENTLIST_H


#include "StudentEntity.h"
#include <vector>

class StudentList {




    vector<StudentEntity> studentList;
public:
    StudentList(string section, string department, int join_year);
    StudentList(string department, int join_year);
    vector<StudentEntity> filterStudentList(string department, string section, int join_year);
    StudentList();
    void addStudent(StudentEntity student);
    void removeStudent(string id);
    void updateStudent(StudentEntity student);
    StudentEntity getStudent(string id);
    vector<StudentEntity> getStudentList();
    StudentList(string department);
};


#endif //LEARNING_MANAGEMENT_SYSTEM_STUDENTLIST_H
