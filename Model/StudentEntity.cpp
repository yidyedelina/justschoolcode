//
// Created by Lenovo on 8/12/2022.
//

#include "StudentEntity.h"
#include "../utility_functions.h"

#include <utility>

StudentEntity::StudentEntity(string* fields) {
   this->Id = fields[0];
   this->Name = fields[1];
   this->Email = fields[2];
   this->age = fields[3];
   this->section = fields[4];
   this->department = fields[5];
   this->join_year = stoi(fields[6]);
}

const string &StudentEntity::getId() const {
    return Id;
}

const string &StudentEntity::getName() const {
    return Name;
}

const string &StudentEntity::getEmail() const {
    return Email;
}

const string &StudentEntity::getAge() const {
    return age;
}

const string &StudentEntity::getSection() const {
    return section;
}

const string &StudentEntity::getDepartment() const {
    return department;
}

int StudentEntity::getJoinYear() const {
    return join_year;
}
string StudentEntity::toString() {
    return Id + "," + Name + "," + Email + "," + age + "," + section + "," + department + "," + to_string(join_year);
}

StudentEntity::StudentEntity(string id) {
    vector<string*> data = loadData("../data/StudentList.csv",7);
    for(auto row : data){
        StudentEntity student(row);
        if(student.getId() == id){
            this->Id = student.getId();
            this->Name = student.getName();
            this->Email = student.getEmail();
            this->age = student.getAge();
            this->section = student.getSection();
            this->department = student.getDepartment();
            this->join_year = student.getJoinYear();
        }
    }
}

void StudentEntity::setName(string basicString) {
    Name = basicString;
}


