//
// Created by Lenovo on 8/12/2022.
//

#ifndef LEARNING_MANAGEMENT_SYSTEM_UTILITY_FUNCTIONS_H
#define LEARNING_MANAGEMENT_SYSTEM_UTILITY_FUNCTIONS_H
#include <string>
#include <vector>
using namespace std;

string *str_to_array(string s, int n, char d);
int validateId(string s);
vector<string *> loadData(string filename, int no_fields);
vector<string> lineData(string filename);
void addData(string filename, string data);
void writeData(string filename, string data);
vector<string> tokenize(string s,char d);
void editData(string filename, string prevData, string newData);
#endif //LEARNING_MANAGEMENT_SYSTEM_UTILITY_FUNCTIONS_H
