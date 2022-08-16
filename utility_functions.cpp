//
// Created by Lenovo on 8/12/2022.
//

#include "utility_functions.h"
#include "Model/StudentList.h"
#include "Model/CourseList.h"
#include "Model/EnrolledCourse.h"
#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include <fstream>
#include <unordered_set>
#include <cstdlib>
using namespace std;
/**
 * @file utils.cpp
 * this file contain a re usable function that we need to build our cli app
 *
 */

/**
 * @brief str_to_array - convert comma separated string to an array of individual string
 *
 * @param s - a comma separated string
 * @param n - a number of words separated by comma
 * @return string* return an array of words
 */
string* str_to_array(string s, int n, char d = ',')
{
    string* token = new string[n];
    stringstream string_stream(s);
    int i = 0;
    while(string_stream.good())
    {
        string a;
        getline(string_stream, a, d);
        token[i] = a;
        i++;
    }
    return token;
}

/**
 * @brief function change string to an vector of string using comma as a delimeter
 *
 * @param filename
 * @return vector<string>
 */
vector<string> lineData(string filename)
{
    vector<string> data;
    ifstream studentfile(filename);
    if(studentfile.is_open())
    {
        string line;
        while(getline(studentfile, line))
        {
            data.push_back(line);
        }
    }
    studentfile.close();
    return data;
}
/**
 * @brief the function load the data from a file and break down them into number of field and store them in vectore
 *
 * @param filename
 * @param no_fields
 * @return vector<string *> a collection of fields
 */
vector<string *> loadData(string filename, int no_fields)
{
    vector<string*> data;
    vector<string> lines = lineData(filename);
    for (int i = 0; i < lines.size(); i++)
    {
        string *s = str_to_array(lines[i], no_fields, ',');
        data.push_back(s);
    }
    return data;
}
/**
 * @brief add a data at the last line of a given file
 *
 * @param filename
 * @param data
 */

void addData(string filename, string data)
{
    ofstream file_out;

    try {
        file_out.open(filename, std::ios_base::app);
        file_out << data << endl;
        file_out.close();
    }catch (exception e){
        cout << "unable to open" << endl;
    }


}
/**
 * @brief a function override the data any file we give it to
 *
 * @param filename: the name of the file we need to write
 * @param data: the data
 */
void writeData(string filename, string data)
{
    ofstream file_out;

    file_out.open(filename);
    file_out << data << endl;
    file_out.close();
}
void editData(string filename, string prevData, string newData){
    vector<string> readFile = lineData(filename);
    vector<string> temp;
    for(auto data : readFile){
        if(data != prevData) temp.push_back(data);
    }
    temp.push_back(newData);
    ofstream file_out(filename);
    for(auto data: temp){
        file_out << data << endl;
    }
    file_out.close();
    cout << "previous data: " << prevData << endl;
    cout << "Replaced by: " << newData << endl;
}

vector<string> tokenize(string s,char d = ',')
{
    vector<string> token;
    stringstream string_stream(s);
    while(string_stream.good())
    {
        string a;
        getline(string_stream, a, d);
        token.push_back(a);
    }
    return token;
}
void generateStudentEnrolledData()
{
    StudentList studentList;
    vector<StudentEntity> list = studentList.getStudentList();
    for(auto student: list){
        int length = 2014 - student.getJoinYear() + 1;
        for(int i = 1; i <= length; i++){
            srand((unsigned) time(NULL));
            CourseList courses(student.getDepartment(), i, 1);
            CourseList courses2(student.getDepartment(), i, 2);
            vector<Course> courseList = courses.getCourseList();
            vector<Course> courseList2 = courses2.getCourseList();
            cout << "course" << courseList[0].getName();
            for(auto course : courseList){
                int grade = 50 + (rand() % 51);
                EnrolledCourse enrolledCourse(course.getId(),student.getId(), grade, 1);
                addData("EnrolledCourseList.txt", enrolledCourse.toString());
            }
            for(auto course : courseList2){
                int grade = 50 + (rand() % 51);
                EnrolledCourse enrolledCourse(course.getId(),student.getId(), grade, 1);
               addData("EnrolledCourseList.txt", enrolledCourse.toString());
            }
        }
    }
}