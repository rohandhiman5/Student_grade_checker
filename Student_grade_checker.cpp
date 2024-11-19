#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

// Define Course structure
struct Courses {
    string courseID;
    string courseName;
    int credits;
};

// Function to return the list of available courses (hardcoded for demonstration)
unordered_map<string, Courses> courseCatalog() {
    unordered_map<string, Courses> courses;
    courses["CSE101"] = {"CSE101", "Introduction to Computer Science", 3};
    courses["CSE102"] = {"CSE102", "Data Structures", 4};
    courses["CSE201"] = {"CSE201", "Operating Systems", 3};
    courses["CSE202"] = {"CSE202", "Algorithms", 4};
    return courses;
}

class student {
public:
    string name;
    long long Roll_no;
    int age;
    string Branch;
    vector<string> registeredCourses;
    int totalCourses;
    unordered_map<string, int> marks_map;
    double CGPA;

    // Constructor to initialize default values
    student() : totalCourses(0), CGPA(0.0) {}

    void getdata();
    void showdata() const;
    void Enter_courses(int);
    double calculateCGPA();
};

// Method to input student data
void student::getdata() {
    cin.ignore(); // Clear input buffer
    cout << "\t* ENTER STUDENT NAME: ";
    getline(cin, name); // Safe input with getline

    cout << "\t* ENTER STUDENT ROLL.NO: ";
    cin >> Roll_no;

    cout << "\t* ENTER STUDENT AGE: ";
    cin >> age;

    cout << "\t* ENTER STUDENT BRANCH: ";
    cin >> Branch;

    cout << "\t* ENTER TOTAL REGISTERED COURSES BY THE STUDENT: ";
    int n;
    cin >> n;

    Enter_courses(n);
}

// Method to display student data
void student::showdata() const {
    cout << "\nSTUDENT NAME: " << name
         << "\nSTUDENT ROLL NO: " << Roll_no
         << "\nSTUDENT AGE: " << age
         << "\nSTUDENT BRANCH: " << Branch
         << "\nTOTAL REGISTERED COURSES: " << totalCourses;

    if (!marks_map.empty()) {
        cout << "\nCOURSES AND MARKS: ";
        for (const auto& course : marks_map) {
            cout << "\n  Course ID: " << course.first
                 << ", Marks: " << course.second;
        }
    }

    cout << "\nCGPA OF STUDENT: " << CGPA << endl;
}

// Method to enter course data
void student::Enter_courses(int n) {
    unordered_map<string, Courses> Temp = courseCatalog();
    totalCourses = 0; // Initialize to 0
    cin.ignore(); // Clear buffer for next input

    while (n--) {
        string courseID;
        cout << "Enter the Course ID: ";
        getline(cin, courseID); // Read course ID

        if (Temp.find(courseID) == Temp.end()) {
            cout << "Course not found! Try again.\n";
            ++n; // Retry the same iteration if course is invalid
        } else {
            registeredCourses.push_back(courseID);

            cout << "Enter marks obtained in " << courseID << ": ";
            int marks;
            cin >> marks;
            marks_map[courseID] = marks;
            cin.ignore(); // Clear buffer for next input
            totalCourses++; // Increment for every valid course entered
        }
    }
}

// Method to calculate CGPA
double student::calculateCGPA() {
    double totalPoints = 0;
    int totalCredits = 0;

    unordered_map<string, Courses> Temp = courseCatalog();
    for (const auto& course : registeredCourses) {
        auto it = Temp.find(course);
        if (it != Temp.end()) {
            totalPoints += it->second.credits * marks_map[course];
            totalCredits += it->second.credits;
        }
    }

    if (totalCredits == 0) {
        return 0.0;
    }
    return totalPoints / totalCredits;
}

// Save all students to file
void saveAllStudentsToFile(const vector<student>& students, const char* filename) {
    ofstream file(filename, ios::out | ios::binary);
    if (!file) {
        cout << "Error opening file for writing.\n";
        return;
    }

    int numStudents = students.size();
    file.write(reinterpret_cast<const char*>(&numStudents), sizeof(numStudents)); // Save the number of students

    for (const auto& s : students) {
        // Write simple data types
        size_t nameLength = s.name.size();
        file.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
        file.write(s.name.c_str(), nameLength);

        file.write(reinterpret_cast<const char*>(&s.Roll_no), sizeof(s.Roll_no));
        file.write(reinterpret_cast<const char*>(&s.age), sizeof(s.age));

        size_t branchLength = s.Branch.size();
        file.write(reinterpret_cast<const char*>(&branchLength), sizeof(branchLength));
        file.write(s.Branch.c_str(), branchLength);

        // Write registered courses
        int totalCourses = s.registeredCourses.size();
        file.write(reinterpret_cast<const char*>(&totalCourses), sizeof(totalCourses));

        for (const auto& course : s.registeredCourses) {
            size_t courseLength = course.size();
            file.write(reinterpret_cast<const char*>(&courseLength), sizeof(courseLength));
            file.write(course.c_str(), courseLength);
        }

        // Write marks_map
        int marksCount = s.marks_map.size();
        file.write(reinterpret_cast<const char*>(&marksCount), sizeof(marksCount));

        for (const auto& entry : s.marks_map) {
            size_t courseLength = entry.first.size();
            file.write(reinterpret_cast<const char*>(&courseLength), sizeof(courseLength));
            file.write(entry.first.c_str(), courseLength);
            file.write(reinterpret_cast<const char*>(&entry.second), sizeof(entry.second));
        }

        // Write CGPA
        file.write(reinterpret_cast<const char*>(&s.CGPA), sizeof(s.CGPA));
    }

    file.close();
}

// Load all students from file
void loadAllStudentsFromFile(vector<student>& students, const char* filename) {
    ifstream file(filename, ios::in | ios::binary);
    if (!file) {
        cout << "Error opening file for reading.\n";
        return;
    }

    int numStudents;
    file.read(reinterpret_cast<char*>(&numStudents), sizeof(numStudents));

    for (int i = 0; i < numStudents; ++i) {
        student s;

        // Read name
        size_t nameLength;
        file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        s.name.resize(nameLength);
        file.read(&s.name[0], nameLength);

        // Read roll number, age, and branch
        file.read(reinterpret_cast<char*>(&s.Roll_no), sizeof(s.Roll_no));
        file.read(reinterpret_cast<char*>(&s.age), sizeof(s.age));

        size_t branchLength;
        file.read(reinterpret_cast<char*>(&branchLength), sizeof(branchLength));
        s.Branch.resize(branchLength);
        file.read(&s.Branch[0], branchLength);

        // Read registered courses
        int totalCourses;
        file.read(reinterpret_cast<char*>(&totalCourses), sizeof(totalCourses));
        s.totalCourses = totalCourses;

        for (int j = 0; j < totalCourses; ++j) {
            size_t courseLength;
            file.read(reinterpret_cast<char*>(&courseLength), sizeof(courseLength));

            string courseID(courseLength, ' ');
            file.read(&courseID[0], courseLength);
            s.registeredCourses.push_back(courseID);
        }

        // Read marks_map
        int marksCount;
        file.read(reinterpret_cast<char*>(&marksCount), sizeof(marksCount));

        for (int j = 0; j < marksCount; ++j) {
            size_t courseLength;
            file.read(reinterpret_cast<char*>(&courseLength), sizeof(courseLength));

            string courseID(courseLength, ' ');
            file.read(&courseID[0], courseLength);

            int marks;
            file.read(reinterpret_cast<char*>(&marks), sizeof(marks));

            s.marks_map[courseID] = marks;
        }

        // Read CGPA
        file.read(reinterpret_cast<char*>(&s.CGPA), sizeof(s.CGPA));

        students.push_back(s);
    }

    file.close();
}

int main() {
    cout<<"working";
    int choice;
    vector<student> students;
    // Load students from file when the program starts
    loadAllStudentsFromFile(students, "students.dat");

    while (true) {
        // Display menu
        cout << "\n*                                                           *\n";
        cout << "*              1. Insert Student Record                    *\n";
        cout << "*              2. View All Student Records                 *\n";
        cout << "*              3. Search Student Record                    *\n";
        cout << "*              4. Delete Student Record                    *\n";
        cout << "*              5. Exit the Program                         *\n";
        cout << "*                                                           *\n";
        cout << "\nEnter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                student newStudent;
                newStudent.getdata();
                newStudent.CGPA = newStudent.calculateCGPA();
                students.push_back(newStudent);
                cout << "\nStudent Record Inserted Successfully!\n";
                break;
            }
            case 2: {
                cout << "\nAll Student Records: \n";
                for (const auto& s : students) {
                    s.showdata();
                    cout << "\n--------------------------------------\n";
                }
                break;
            }
            case 3: {
                long long rollNo;
                cout << "Enter Roll No to Search: ";
                cin >> rollNo;

                bool found = false;
                for (const auto& s : students) {
                    if (s.Roll_no == rollNo) {
                        s.showdata();
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "Student with Roll No " << rollNo << " not found.\n";
                }
                break;
            }
            case 4: {
                long long rollNo;
                cout << "Enter Roll No to Delete: ";
                cin >> rollNo;

                auto it = remove_if(students.begin(), students.end(), [rollNo](const student& s) {
                    return s.Roll_no == rollNo;
                });

                if (it != students.end()) {
                    students.erase(it, students.end());
                    cout << "Student with Roll No " << rollNo << " deleted.\n";
                } else {
                    cout << "Student with Roll No " << rollNo << " not found.\n";
                }
                break;
            }
            case 5: {
                // Save students to file before exiting
                saveAllStudentsToFile(students, "students.dat");
                cout << "Exiting Program...\n";
                return 0;
            }
            default:
                cout << "Invalid choice, please try again.\n";
        }
    }

    return 0;
}