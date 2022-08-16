cmake_minimum_required(VERSION 3.22)
project(Learning_management_system)

set(CMAKE_CXX_STANDARD 14)

add_executable(Learning_management_system main.cpp Model/StudentEntity.cpp Model/StudentEntity.h Model/StudentList.cpp Model/StudentList.h Model/Course.cpp Model/Course.h utility_functions.cpp utility_functions.h Model/CourseList.cpp Model/CourseList.h Model/EnrolledCourse.cpp Model/EnrolledCourse.h Model/EnrolledCourseList.cpp Model/EnrolledCourseList.h Services/LearningManagementService.cpp Services/LearningManagementService.h Page/Views.cpp Page/Views.h Exceptions/Exceptions.h Exceptions/NumberOfArgumentException.cpp)
