#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include "courseCatalog.h"

using namespace std;

struct GradePolicy {
    int LowerBound;
    int UpperBound;
    char Grade;
};

class student {
private:
    char name[30];
    long long Roll_no;
    int age;
    char Branch[10];
    vector<string> Courses_ID;
    unordered_map<string, int> marks_map;
    double CGPA;

    string convert(string s);

public:
    student(); // Constructor

    void ccolor(int clr); // Display colorful content
    void getdata(); // Get all data from the user
    void showdata(); // Display all data
    void viewAlldata(); // Display all data from file
    int storedata(); // Store all data in a file
    void searchData(char *); // Search for particular data
    void showsearch(); // Display search option
    void deleteData(char *); // Delete a record
    void updateData(char *); // Update a record
    void Enter_courses(int); // Enter course information
    void Calculate_CGPA(); // Calculate CGPA
};

#endif // STUDENT_H
