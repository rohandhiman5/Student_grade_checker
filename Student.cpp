#include "student.h"
#include "courseCatalog.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <windows.h>

using namespace std;

student::student() {
    Roll_no = 0;
    age = 0;
    CGPA = 0.0;
    strcpy(Branch, "N/A");
    strcpy(name, "N/A");
}

string student::convert(string s) {
    for (int i = 0; i < s.length(); i++) {
        s[i] = toupper(s[i]);
    }
    return s;
}

void student::ccolor(int clr) {
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, clr);
}

void student::getdata() {
    fflush(stdin);
    cout << "\t* ENTER STUDENT NAME :";
    cin.getline(name, 29);
    fflush(stdin);
    cout << "\t* ENTER STUDENT ROLL.NO :";
    cin >> Roll_no;
    fflush(stdin);
    cout << "\t* ENTER STUDENT AGE :";
    cin >> age;
    fflush(stdin);
    cout << "\t* Enter Total registered courses by the student";
    int n;
    cin >> n;
    cout << endl;
    Enter_courses(n);
}

void student::Enter_courses(int n) {
    fflush(stdin);
    int i = 0;
    while (n--) {
        cout << "Enter the Course Id" << endl;
        cin >> Courses_ID[i];
        i++;
        cout << "Enter Marks obtained in that course:" << endl;
        cin >> marks_map[Courses_ID[i]]; // hashing
    }
}

void student::Calculate_CGPA() {
    fflush(stdin);
    vector<GradePolicy> gradePolicy = {
        {90, 100, 'A'},  // A = 10
        {80, 89, 'B'},   // B = 8
        {70, 79, 'C'},   // C = 6
        {60, 69, 'D'},   // D = 4
        {50, 59, 'E'},   // E = 2
        {0, 49, 'F'}     // F = 0
    };

    unordered_map<char, int> gradePoints = {
        {'A', 10}, {'B', 8}, {'C', 6}, {'D', 4}, {'E', 2}, {'F', 0}
    };

    double totalGradePoints = 0;
    int totalCredits = 0;

    for (const auto& course : Courses_ID) {
        string courseId = convert(course); // Convert to uppercase for consistency
        if (marks_map.find(courseId) != marks_map.end()) {
            int marks = marks_map[courseId];

            // Find the grade for the marks
            char grade = 'F'; // Default grade
            for (const auto& policy : gradePolicy) {
                if (marks >= policy.LowerBound && marks <= policy.UpperBound) {
                    grade = policy.Grade;
                    break;
                }
            }

            // Get grade points
            int points = gradePoints[grade];

            extern unordered_map<string, Courses> courseCatalog; // Declare the catalog
            if (courseCatalog.find(courseId) != courseCatalog.end()) {
                int credits = courseCatalog[courseId].credits;

                // Add to totals
                totalGradePoints += (points * credits);
                totalCredits += credits;
            }
        }
    }

    // Calculate CGPA
    if (totalCredits > 0) {
        CGPA = totalGradePoints / totalCredits;
    } else {
        CGPA = 0.0; // No courses, no CGPA
    }

    cout << "Calculated CGPA: " << CGPA << endl;
}

void student::showdata() {
    cout << "\t|NAME of the student is       |->    " << name << "   " << endl;
    cout << "\t|                             |                   " << endl;
    cout << "\t|Roll.NO of the student is    |->       " << Roll_no << "          " << endl;
    cout << "\t|Age of the student is        |->        " << age << "         " << endl;
    cout << "\t|                             |                   " << endl;
}

int student::storedata() {
    if (age == 0 && Roll_no == 0) {
        cout << "\n Student data not initialized : ";
        return (0);
    } else {
        ofstream fout;
        fout.open("file.dat", ios::app | ios::binary);
        fout.write((char*)this, sizeof(*this));
        fout.close();
        return (1);
    }
}

void student::viewAlldata() {
    ifstream fin;
    fin.open("file.dat", ios::in | ios::binary);
    if (!fin)
        cout << "Error: file not found:";
    else {
        fin.read((char*)this, sizeof(*this));
        while (!fin.eof()) {
            showdata();
            fin.read((char*)this, sizeof(*this));
        }
        fin.close();
    }
}

void student::searchData(char* t) {
    int count = 0;
    ifstream fin;
    fin.open("file.dat", ios::in | ios::binary);
    if (!fin)
        cout << "Error: file not found:";
    else {
        fin.read((char*)this, sizeof(*this));
        while (!fin.eof()) {
            if (!strcmp(t, name)) {
                showdata();
                count++;
            }
            fin.read((char*)this, sizeof(*this));
        }
        if (count == 0)
            cout << "\n Record not found:";
        fin.close();
    }
}

void student::showsearch() {
    cout << "\t\t*************************************" << "\n";
    cout << "\t\t*                                   *" << "\n";
    cout << "\t\t*      STUDENT SEARCH OPTION        *" << "\n";
    cout << "\t\t*                                   *" << "\n";
    cout << "\t\t*************************************" << "\n";
    char ser[30];
    cout << "\t\t Enter Name of the student:";
    fflush(stdin);
    cin.getline(ser, 29);
    searchData(ser);
}

void student::deleteData(char* t) {
    ifstream fin;
    ofstream fout;
    fin.open("file.dat", ios::in | ios::binary);
    if (!fin) {
        ccolor(12);
        cout << "Error: file not found:";
    } else {
        fout.open("temp.dat", ios::out | ios::binary);
        fin.read((char*)this, sizeof(*this));
        while (!fin.eof()) {
            if (strcmp(name, t))
                fout.write((char*)this, sizeof(*this));
            fin.read((char*)this, sizeof(*this));
        }
        fin.close();
        fout.close();
        remove("file.dat");
        rename("temp.dat", "file.dat");
    }
}

void student::updateData(char* t) {
    fstream file;
    file.open("file.dat", ios::in | ios::out | ios::ate | ios::binary);
    file.seekg(0);
    file.read((char*)this, sizeof(*this));
    while (!file.eof()) {
        if (!strcmp(t, name)) {
            getdata();
            file.seekp(file.tellp() - sizeof(*this));
            file.write((char*)this, sizeof(*this));
        }
        file.read((char*)this, sizeof(*this));
    }
}
