//
// Created by Lenovo on 8/12/2022.
//

#include "Views.h"
#include "../utility_functions.h"
#include "../Services/LearningManagementService.h"
#include "../Exceptions/Exceptions.h"
#include <iostream>
#include <string>
using namespace std;
void Views::homePage() {
    string input;
    LearningManagementService service;
    while(input != "exit")
    {
        cout << "(AASTU LMS)$ ";
        getline(cin, input);
        vector<string> parsedInput = tokenize(input, ' ');
        string command = parsedInput[0];

        if(command == "mark")
        {
            try{
                vector<StudentMark> s = service.MarkCommand(parsedInput);
                seeSectionScore(s);
            } catch(ValidationErrorException e)
            {
                cout << e.what() << endl;
            } catch(NumberOfArgumentException e)
            {
                cout << e.what() << endl;
            }
        }
        else if(command == "register")
        {
            try{
                service.RegisterCommand(parsedInput);
            }catch(ValidationErrorException e){
                cout << e.what() << endl;
            }
        }
        else if(command == "search"){
            try{
                service.SearchCommand(parsedInput[1]);
            }catch(ValidationErrorException e){
                cout << e.what() << endl;
            }


        }
        else if(command == "edit"){
            try{
                service.EditCommand(parsedInput);
            }catch(ValidationErrorException e){
                cout << e.what() << endl;
            }
        }
        else if(command == "add"){
            try{
                service.AddGradeCommand(parsedInput);
            }catch(ValidationErrorException e){
                cout << e.what() << endl;
            }
        }
        else if(command == "filter"){
            try {
                seeSectionScore(service.FilterCommand(parsedInput));
            }catch(ValidationErrorException e){
                cout << e.what() << endl;
            }
        }
        else if(command == "list"){
            try {
                service.ListCommand(parsedInput);
            }catch(ValidationErrorException e){
                cout << e.what() << endl;
            }
        }
        else if(command == "generate"){
            service.generateStudentEnrolledData();
        }
        else cout << "Invalid Command" << "\n";
    }
}

Views::Views() {

}

void Views::studentMarkPage() {
    char* menu[] = {"See section score", "see student score"};
    for(int i = 0; i < 2; i++) {
        cout << i + 1 << ". " << menu[i] << endl;
    }
    int choice;
    cin>>choice;
    switch(choice)
    {
        case 1:
            break;
        case 2:

            break;

    }
}

void Views::printString(int number, char s) const {
    for(int i = 0; i < number; i++)
    {
        cout << s;
    }
    cout << endl;
}
void Views::seeSectionScore(vector<StudentMark> studentMark)
{



    if(studentMark.size() ==  0)
    {
        cout << "No data available" << endl;
        return;
    }
    printString((studentMark[0].grades.size())*17 + 38, '-');
    printf("|%-30s|", "Name");

    for(auto header: studentMark[0].grades)
    {
        printf("%-15s |", header.subjectName.substr(0,15).c_str());
    }
    printf("GPA |\n");
    printString((studentMark[0].grades.size())*17 + 38, '-');
    for(auto mark : studentMark) {
        printf("|%-30s|", mark.name.c_str());
        for(auto grade: mark.grades)
        {
            printf("%-15.2f |", grade.mark);
        }
        printf("%.2f|\n", mark.gpa);
    }
}

void Views::seeStudentScore(StudentMark* studentMark) {

    if(studentMark->gpa)
    {
        cout << "No data Available" << endl;
        return;
    }
    cout << "Student: " << studentMark->name << endl;
    cout << "GPA:" << studentMark->gpa << endl;
    for(auto grade: studentMark->grades)
    {
        cout << grade.subjectName << ": " << grade.mark <<endl;
    }
}
