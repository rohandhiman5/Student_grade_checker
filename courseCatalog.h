#ifndef COURSE_CATALOG_H
#define COURSE_CATALOG_H

#include <unordered_map>
#include <string>
#include <cstring>
using namespace std;

// Define the Courses class
class Courses {
public:
    char Course_code[10];
    int credits;
    char Course_name[50];

    // Constructor
    Courses() {
        strcpy(Course_code, "N/A");
        credits = 0;
        strcpy(Course_name, "N/A");
    }

    Courses(const char* code, int cred, const char* name) {
        strcpy(Course_code, code);
        credits = cred;
        strcpy(Course_name, name);
    }
};

// Declare the global course catalog
extern unordered_map<string, Courses> courseCatalog;

// Function to initialize the course catalog
void initializeCourseCatalog();

#endif
