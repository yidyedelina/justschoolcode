//
// Created by Lenovo on 8/12/2022.
//

#include "StudentList.h"
#include "../utility_functions.h"


StudentList::StudentList(string section, string department, int join_year) {
    vector<string*> data = loadData("../data/StudentList.csv",7);
    for(auto row : data){
        StudentEntity student(row);
        if(student.getSection() == section && student.getDepartment() == department && student.getJoinYear() == join_year){
            this->studentList.push_back(student);
        }
    }
}
StudentList::StudentList(string department, int join_year) {
    vector<string*> data = loadData("../data/StudentList.csv",7);
    for(auto row : data){
        StudentEntity student(row);
        if(student.getDepartment() == department && student.getJoinYear() == join_year){
            this->studentList.push_back(student);
        }
    }
}
StudentList::StudentList(string department) {
    vector<string*> data = loadData("../data/StudentList.csv",7);
    for(auto row : data){
        StudentEntity student(row);
        if(student.getDepartment() == department){
            this->studentList.push_back(student);
        }
    }
}

vector<StudentEntity> StudentList::getStudentList() {
    return this->studentList;
}

StudentEntity StudentList::getStudent(string id) {
    for(auto student : this->studentList){
        if(student.getId() == id){
            return student;
        }
    }
    StudentEntity studentEntity(id);
    return studentEntity;
}

void StudentList::addStudent(StudentEntity student) {

}

StudentList::StudentList() {
    vector<string*> data = loadData("../data/StudentList.csv",7);
    for(auto row : data){
        StudentEntity student(row);
        this->studentList.push_back(student);
    }
}

vector<StudentEntity> StudentList::filterStudentList(string department, string section, int join_year) {
    vector<StudentEntity> filteredData;
    for(auto student: studentList){
        if(student.getDepartment() == department && student.getSection() == section && student.getJoinYear() == join_year){
            filteredData.push_back(student);
        }
    }
    return filteredData;
}

