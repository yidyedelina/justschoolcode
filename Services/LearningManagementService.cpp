//
// Created by Lenovo on 8/12/2022.
//

#include "LearningManagementService.h"

#include <utility>
#include <iostream>
#include <regex>
#include <iomanip>
#include "../Exceptions/Exceptions.h"
#include "../utility_functions.h"

double CGPA(string id);

vector<StudentMark> LearningManagementService::getStudentsMark(string department, string section, int join_year, int year, int semester) {
    vector<StudentEntity> students = studentListRef->filterStudentList(department,section, join_year);
    vector<StudentMark> studentMarks;
    for(auto student : students){
        StudentMark studentMark;
        studentMark.name = student.getName();
        vector<EnrolledCourse> enrolledCourse = enrolledCourseListRef->filterEnrolledCourseMap(student.getId(), year, semester);
        studentMark.gpa = CalculateGpa(enrolledCourse);

        for(auto enrollCourse : enrolledCourse){
            Grade grade;
            grade.subjectName = courseListRef->getCourse(enrollCourse.getCourseCode()).getName();
            grade.mark = enrollCourse.getGrade();
            studentMark.grades.push_back(grade);
        }
        studentMarks.push_back(studentMark);
    }
    return studentMarks;
}

LearningManagementService::LearningManagementService() {
    enrolledCourseListRef = new EnrolledCourseList;
    courseListRef = new CourseList;
    studentListRef =  new StudentList;
}

StudentMark LearningManagementService::getStudentMark(string id, int year, int semester) {
    vector<EnrolledCourse> enrolledCourseList = enrolledCourseListRef->filterEnrolledCourseMap(id,year, semester);
    StudentMark studentMark;
    studentMark.name = studentListRef->getStudent(id).getName();
    studentMark.gpa = CalculateGpa(enrolledCourseList);
    for(auto enrolledCourse : enrolledCourseList){
        Grade grade;
        Course ptr = courseListRef->getCourse(enrolledCourse.getCourseCode());
        grade.subjectName = ptr.getName();
        grade.mark = enrolledCourse.getGrade();
        grade.creditHour = ptr.getCreditHour();
        studentMark.grades.push_back(grade);
    }
    return studentMark;
}

vector<StudentMark> LearningManagementService::MarkCommand(vector<string> parsedData) {
    int length = parsedData.size();
    vector<StudentMark> studentMark = {};
    if (length < 3 || length > 6) {
        throw NumberOfArgumentException();
    }
    if (parsedData[1] == "-s") {
        if (validateId(parsedData[2]) == 0) {
            cout << "I have found error" << endl;
        }
        StudentEntity studentEntity(parsedData[2]);
        if(parsedData.size() == 3)
        {
            cumulative_display(parsedData[2]);
            return studentMark;
        }
        int year, semester;
        try {
            year = stoi(parsedData[3]);
            semester = stoi(parsedData[4]);
        } catch (invalid_argument e) {
            throw ValidationErrorException("can't convert to number");
        }
        if (year > 0 && year < 6) {
            year = studentEntity.getJoinYear() + year - 1;
        }
        if (year > current_year || year < studentEntity.getJoinYear()) {
            throw ValidationErrorException("We can't find data for this year");
        }
        if (semester > 2 || semester < 0){
           throw ValidationErrorException("Invalid semester input");
        }
        if(year == current_year && semester > current_semester)
        {
            throw ValidationErrorException("Invalid semester input");
        }
        if(parsedData.size() == 5){
            StudentMark s = getStudentMark(parsedData[2],year - studentEntity.getJoinYear()  + 1, semester);
            studentMark.push_back(s);
            return studentMark;
        }

    }
    validateDepartment(parsedData[1]);
    if(parsedData[2].size() > 2)
    {
        throw ValidationErrorException("section can't be morethan one letter");
    }
    int batch_year, academic_year, semester;
    try {
        batch_year = stoi(parsedData[3]);
        academic_year = stoi(parsedData[4]);
        semester = stoi(parsedData[5]);
    }catch(invalid_argument e){
        cout << "Can't convert to a number" << endl;
    }
    if(batch_year < 2010 || batch_year > current_year)
        throw ValidationErrorException("Invalid batch_year Inserted");
    if(academic_year < batch_year || academic_year > current_year)
        throw ValidationErrorException("Invalid academic year");
    if(semester > 2 || semester < 0)
        throw ValidationErrorException("Invalid Semester input");
    studentMark = getStudentsMark(parsedData[1], parsedData[2], batch_year, academic_year - batch_year + 1, semester);
    return studentMark;
}

int LearningManagementService::validateId(string Id){
    regex b("^(ets)[0-9]{4}(/[0-1][0-4])$");
    if(regex_match(Id, b) == 0)
    {
        throw ValidationErrorException("Invalid Id format");
    }
    StudentEntity studentEntity = studentListRef->getStudent(Id);
    if(studentEntity.getName().empty())
    {
        throw ValidationErrorException("No student found with this Id");
    }
    return 1;
}

void LearningManagementService::validateDepartment(string dep) {
    for(int i = 0; i < 3; i++)
    {
        if(dep == departments[i])
        {
            return;
        }
    }
    throw ValidationErrorException("can't find the department");
}

void LearningManagementService::RegisterCommand(vector<string> parsedData) {
    if(parsedData.size() != 2)
    {
       throw ValidationErrorException("Invalid Input enter -help for doc");
    }
    regex b("^(ets)[0-9]{4}(/[0-1][0-4])$");
    if(regex_match(parsedData[1], b) == 0)
    {
        throw ValidationErrorException("Invalid Id format");
    }
    StudentEntity studentEntity(parsedData[1]);
    if(studentEntity.getName() != "")
    {
        cout << "The student already exist in the database do you want to register for new semester yes/no" << endl;
        string input;
        getline(cin, input);
        //TODO: implement registration logic for existing student;
        if(input == "yes" || input == "y"){
            vector<Course> courses = courseListRef->getCourseList(studentEntity.getDepartment(), current_year - studentEntity.getJoinYear() + 1, current_semester);
            vector<EnrolledCourse> enrolledCourse = enrolledCourseListRef->filterEnrolledCourseMap(studentEntity.getId(), current_year - studentEntity.getJoinYear() + 1, current_semester);
            
        }
        return;
    }
    string firstname, lastname, email, section;
    cout << "Enter the student data [firstname] [lastname] [email] [age] [section]";
    string data;
    getline(cin, data);
    vector<string> parsedStudent = tokenize(data, ' ');
    if(parsedStudent.size() != 5){
        throw ValidationErrorException("Invalid input");
    }
    firstname = parsedStudent[0];
    lastname = parsedStudent[1];
    email = parsedStudent[2];
    section = parsedStudent[4];

    regex name("[a-zA-Z]+");
    if(regex_match(firstname, name) == 0 || regex_match(lastname, name) == 0)
    {
        throw ValidationErrorException("Invalid name format");
    }
    regex emailreg("^[a-zA-Z0-9.!#$%&’*+/=?^_`{|}~-]+@[a-zA-Z0-9-]+(?:\\.[a-zA-Z0-9-]+)*$");
    if(regex_match(email, emailreg) == 0)
    {
        throw ValidationErrorException("Invalid Email format");
    }
    int age;
    try{
        age = stoi(parsedStudent[3]);
    }catch(invalid_argument e)
    {
        cout << "can't convert to number" << endl;
    }
    if(age < 16 && age > 60)
    {
        throw ValidationErrorException("Age must be between 16-60");
    }
    regex sectionreg("[A-Z]");
    if(section.size() > 1 && regex_match(section, sectionreg)){
        throw ValidationErrorException("Invalid section insert");
    }
    string csvdata = parsedData[1] + "," + firstname +" "+ lastname + "," + email +  "," + to_string(age) + "," + section + "," + "freshman_engineering" +  "," +to_string(current_year);

    addData("../data/StudentList.csv", csvdata);
}

void LearningManagementService::SearchCommand(string id) {
    validateId(id);
    StudentEntity studentEntity = studentListRef->getStudent(id);
    if(studentEntity.getName() == "")
    {
        throw ValidationErrorException("student doesn't exist");
    }
    cout << "Name:" << studentEntity.getName() << endl;
    cout << "Age:" << studentEntity.getAge() << endl;
    cout << "Email:" << studentEntity.getEmail() << endl;
    cout << "Department:" << studentEntity.getDepartment() << endl;
    cout << "Section:" << studentEntity.getSection() << endl;
    cumulative_display(id);
}

void LearningManagementService::cumulative_display(string &id) {
    StudentMark score = CGPA(id);
    cout << "CGPA:" << setprecision(2) <<score.gpa << endl;
    int i = 1;
    for(auto semesterGrade: score.grades){
        cout << semesterGrade.subjectName << ":: "<< setprecision(2) << semesterGrade.mark << "\t\t";
        if(i % 2 == 0){
            cout << endl;
        }
        i++;
    }
}

void LearningManagementService::EditCommand(vector<string> parsedData) {
    if(parsedData.size() != 2 && parsedData.size() != 4)
    {
        throw ValidationErrorException("Invalid number of argument");
    }
    //TODO:Edit student data
    if(parsedData.size() == 2){
        validateId(parsedData[1]);
        StudentEntity studentEntity(parsedData[1]);
        cout << "student name:" << studentEntity.getName() << endl;
        cout << "Enter the student firstname you want to change: " << endl;
        string firstname;
        string lastname;
        getline(cin, firstname);
        cout << "Enter the student lastname you want to change: " << endl;
        getline(cin, lastname);

        regex name("[a-zA-Z]+");
        if(regex_match(firstname, name) == 0 || regex_match(lastname, name) == 0)
        {
            throw ValidationErrorException("Invalid name format");
        }
        string fullname = firstname + " " + lastname;
        string prevData = studentEntity.toString();
        studentEntity.setName(fullname);
        string newData = studentEntity.toString();
        editData("../data/StudentList.csv", prevData, newData);
        return;
    }
    string course_id = parsedData[1];
    string student_id = parsedData[2];
    Course course(course_id);
    validateId(student_id);
    EnrolledCourseList enrolledCourse(student_id, course.getYear(), course.getSemester());
    EnrolledCourse foundCourse = enrolledCourse.getEnrolledCourse(course_id);
    if(foundCourse.getCourseCode() == ""){
        throw ValidationErrorException("No course Found");
    }
    double mark;
    try {
        mark = stof(parsedData[3]);
    }catch(invalid_argument e){
        throw ValidationErrorException("Can't convert to number");
    }
    if(mark < 0 || mark > 100){
        throw ValidationErrorException("Invalid range of mark");
    }
    string prevData = foundCourse.toString();
    foundCourse.setGrade(mark);
    string newData = foundCourse.toString();
    editData("../data/EnrolledCourseList.csv", prevData, newData);
}

void LearningManagementService::AddGradeCommand(vector<string> parsedData) {
    if(parsedData.size() != 2){
        throw ValidationErrorException("Invalid number of argument");
    }
    validateId(parsedData[1]);
    StudentEntity studentEntity = studentListRef->getStudent(parsedData[1]);
    vector<EnrolledCourse> list = enrolledCourseListRef->filterEnrolledCourseList(parsedData[1], current_year - studentEntity.getJoinYear() + 1, current_semester);
    for(auto li: list){
        if(li.getStatus() == 0){
            string input;
            Course cr(li.getCourseCode());
            cout <<"Enter the grade for " << cr.getName() << ": ";
            getline(cin, input);
            double grade;
            try{
                grade = stof(input);
            }catch(invalid_argument e){
                cout << "can't convert to number" << endl;
            }
            validateGrade(grade);
            string prevData = li.toString();
            li.setGrade(grade);
            li.setStatus(1);
            string newData = li.toString();
            editData("../data/EnrolledCourseList.csv", prevData, newData);
        }
        return;
    }
}

void LearningManagementService::validateGrade(double grade) {
    if(grade < 0 || grade > 100){
        throw ValidationErrorException("Invalid range of mark");
    }
}

vector<StudentMark> LearningManagementService::FilterCommand(vector<string> parsedData) {
    if(parsedData.size() != 5){
        throw ValidationErrorException("Invalid number of argument");
    }
    int top;
    int year;
    try{
        top = stoi(parsedData[2]);
        year = stoi(parsedData[4]);
    }catch(invalid_argument e){
        throw ValidationErrorException("Can't convert to a number");
    }
    if(top < 3 || top > 10){
        throw ValidationErrorException("The value should be between 3 - 10");
    }
    string department = parsedData[3];
    validateDepartment(department);
    StudentList studentList(department,year);
    vector<StudentMark> studentMarkList;
    vector<StudentEntity> studentLi = studentList.getStudentList();
    for(auto student: studentLi){
        StudentMark s = CGPA(student.getId());
        studentMarkList.push_back(s);
    }
    vector<StudentMark> top_student;
    string condition = parsedData[1]; // whether bottom or top
    if(condition != "bottom" && condition != "top"){
        throw ValidationErrorException("Invalid second argument");
    }
    if(condition == "bottom")
        sort(studentMarkList.begin(), studentMarkList.end(), lessGpa);
    else
        sort(studentMarkList.begin(), studentMarkList.end(), greatGpa);
    if(top > studentMarkList.size()){
        for(int i = 0; i < studentMarkList.size(); i++){
            top_student.push_back(studentMarkList[i]);
        }
    }
    else {
        for(int i = 0; i < top; i++){
            top_student.push_back(studentMarkList[i]);
        }
    }
    return top_student;
}

StudentMark LearningManagementService::CGPA(string id) {
    StudentEntity studentEntity = studentListRef->getStudent(id);
    int total_year = current_year - studentEntity.getJoinYear() + 1;
    double total = 0;
    double total_credit = 0;
    vector<StudentMark> studentMark;
    for(int i = 0; i < total_year; i++)
    {
        StudentMark student1 = getStudentMark(id, i + 1, 1);
        studentMark.push_back(student1);
        if(current_year == studentEntity.getJoinYear() + i + 2 && current_semester != 2)
        {
            break;
        }
        StudentMark student2 = getStudentMark(id, i + 1, 2);
        studentMark.push_back(student2);
    }
    StudentMark cumulative_grade;
    cumulative_grade.name = studentEntity.getName();
    int sem = 1;
    int year = 1;
    for(auto student : studentMark){
        double semesterCredit = 0;
        double semesterTotal = 0;
        for(auto grade: student.grades){
           semesterCredit += grade.creditHour;
        }
        semesterTotal = student.gpa * semesterCredit;
        total += semesterTotal;
        total_credit += semesterCredit;
        Grade gr;
        if(sem > 2){
            sem = 1;
            year++;
        }
        gr.subjectName = "Academic Year " + to_string(year) + " Semester " + to_string(sem);
        gr.creditHour = semesterCredit;
        gr.mark = semesterTotal /  semesterCredit;
        cumulative_grade.grades.push_back(gr);
        sem++;
    }
    cumulative_grade.gpa = total/total_credit;
    return cumulative_grade;
}
//list course software_engineerign 2 1
vector<StudentMark> LearningManagementService::ListCommand(vector<string> parsedInput) {

    if(parsedInput[1] == "course"){
        if(parsedInput.size() != 5){
            throw ValidationErrorException("Invalid number of argument");
        }
        validateDepartment(parsedInput[2]);
        int year;
        int semester;
        try {
            year = stoi(parsedInput[4]);
            semester = stoi(parsedInput[3]);
        }catch(invalid_argument ex){
            throw ValidationErrorException("Can't convert to a number");
        }
        if(year < 1 || year > 4){
            throw ValidationErrorException("The range should be 1 to 4");
        }
        CourseList courseList(parsedInput[2], year, semester);
        vector<Course> courseList1 = courseList.getCourseList();
        listCourse(courseList1);
        return vector<StudentMark>();
    }
    if(parsedInput.size() != 4){
        throw ValidationErrorException("Invalid number of argument");
    }
    string condition = parsedInput[1];
    if(condition != "gt" && condition != "lt"){
        throw ValidationErrorException("Invalid second argument");
    }
    float gpa;
    try{
        gpa = stof(parsedInput[2]);
    }catch(invalid_argument e){
        throw ValidationErrorException("Can't change to a number");
    }
    validateDepartment(parsedInput[3]);
    StudentList studentList(parsedInput[3]);
    vector<StudentMark> studentMarkList;
    vector<StudentEntity> studentLi = studentList.getStudentList();
    for(auto student: studentLi){
        StudentMark s = CGPA(student.getId());
        studentMarkList.push_back(s);
    }
    vector<StudentMark> filteredMarkList;
    int i = 0;
    for(auto studentMark : studentMarkList){
        if(condition == "gt"){
            if(studentMark.gpa > gpa) filteredMarkList.push_back(studentMark);
        }
        else{
            if(studentMark.gpa < gpa) filteredMarkList.push_back(studentMark);
        }
    }
    return filteredMarkList;
}

void LearningManagementService::listCourse(vector<Course> courseList){
   for(auto course: courseList){
       cout << course.getName() << ": " << "Credit Hour: " << course.getCreditHour() << endl;
   }
}



void LearningManagementService::generateStudentEnrolledData()
{
    StudentList studentList;
    vector<StudentEntity> list = studentList.getStudentList();
    for(auto student: list){
        int length = 2014 - student.getJoinYear() + 1;
        int num = 80;
        for(int i = 1; i <= length; i++){
            srand((unsigned int) num++);
            CourseList courses(student.getDepartment(), i, 1);
            CourseList courses2(student.getDepartment(), i, 2);
            vector<Course> courseList = courses.getCourseList();
            vector<Course> courseList2 = courses2.getCourseList();
            for(auto course : courseList){
                int grade = 40 + ((rand() + course.getCreditHour() + course.getSemester() + student.getName().size() + course.getName().size()) % 61);
                EnrolledCourse enrolledCourse(course.getId(),student.getId(), grade, 1);
                addData("../data/EnrolledCourseList.csv", enrolledCourse.toString());
            }
            for(auto course : courseList2){
                int grade = 40 + ((rand() + course.getCreditHour() + course.getSemester() + student.getName().size() + course.getName().size()) % 61);
                EnrolledCourse enrolledCourse(course.getId(),student.getId(), grade, 1);
                addData("../data/EnrolledCourseList.csv", enrolledCourse.toString());
            }
        }
    }
}

unordered_map<string, float> gradeReference = {{"A+", 4}, {"A", 4}, {"A-", 3.75}, {"B+", 3.5}, {"B", 3}, {"B-", 2.75}, {"C+", 2.5}, {"C", 2}, {"C-", 1.75}, {"D", 1}, {"F", 0}};

double LearningManagementService::CalculateGpa(vector<EnrolledCourse> enrolledCourseList) {
    double total_credit_hour = 0;
    double total_mark = 0;
    for(auto enrolledCourse : enrolledCourseList){
        Course course = courseListRef->getCourse(enrolledCourse.getCourseCode());
        total_credit_hour += course.getCreditHour();
        total_mark += gradeReference[enrolledCourseListRef->MarkToLetterGrade(enrolledCourse.getGrade())] * course.getCreditHour();
    }
    return total_mark / total_credit_hour;
}