#include "CourseCatalog.h"

unordered_map<string, Courses> courseCatalog;

void initializeCourseCatalog() {
    courseCatalog["CS101"] = Courses("CS101", 4, "Data Structures");
    courseCatalog["MA101"] = Courses("MA101", 3, "Calculus");
    courseCatalog["PH101"] = Courses("PH101", 2, "Physics");
    courseCatalog["EE101"] = Courses("EE101", 3, "Electrical Circuits");
}


