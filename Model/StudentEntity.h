//
// Created by Lenovo on 8/12/2022.
//

#ifndef LEARNING_MANAGEMENT_SYSTEM_STUDENTENTITY_H
#define LEARNING_MANAGEMENT_SYSTEM_STUDENTENTITY_H
#include <string>
#include <vector>
using namespace std;

class StudentEntity {
    string Id;
    string Name;
    string Email;
    string age;
    string section;
    string department;
    int join_year;
public:
    const string &getId() const;

    const string &getName() const;

    const string &getEmail() const;

    const string &getAge() const;

    const string &getSection() const;

    const string &getDepartment() const;

    int getJoinYear() const;
    string toString();
    StudentEntity(string* fields);
    StudentEntity(string id);

    void setName(string basicString);
};


#endif //LEARNING_MANAGEMENT_SYSTEM_STUDENTENTITY_H
