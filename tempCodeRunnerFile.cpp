#include<iostream>
#include "CourseCatalog.h" // Include your header file
#include "Student.h"       // Separate the `student` class into its own header and implementation files

using namespace std;

int main() {
    student s1;
    int choice;

    // Display welcome screen and login
    s1.ccolor(14); // Set initial console color
    cout << "Welcome to the Student Management System!" << endl;

    while (true) {
        system("cls"); // Clear screen for better readability
        cout << "*****************************************************************" << "\n";
        cout << "***                                                           ***" << "\n";
        cout << "***              1. Insert Student Record                    ***" << "\n";
        cout << "***              2. View All Student Records                 ***" << "\n";
        cout << "***              3. Search Student Record                   ***" << "\n";
        cout << "***              4. Delete Student Record                   ***" << "\n";
        cout << "***              5. Update Student Record                   ***" << "\n";
        cout << "***              6. Exit                                     ***" << "\n";
        cout << "***                                                           ***" << "\n";
        cout << "*****************************************************************" << "\n";
        cout << "\nEnter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: { // Insert a new student record
                s1.getdata();
                if (s1.storedata()) {
                    cout << "\nStudent record stored successfully." << endl;
                } else {
                    cout << "\nFailed to store the student record." << endl;
                }
                break;
            }
            case 2: { // View all student records
                cout << "\nDisplaying all student records:\n";
                s1.viewAlldata();
                break;
            }
            case 3: { // Search for a specific student record
                cout << "\nEnter the name of the student to search: ";
                char name[30];
                cin.ignore(); // Clear the input buffer
                cin.getline(name, 30);
                s1.searchData(name);
                break;
            }
            case 4: { // Delete a student record
                cout << "\nEnter the name of the student to delete: ";
                char name[30];
                cin.ignore();
                cin.getline(name, 30);
                s1.deleteData(name);
                cout << "\nStudent record deleted successfully." << endl;
                break;
            }
            case 5: { // Update a student record
                cout << "\nEnter the name of the student to update: ";
                char name[30];
                cin.ignore();
                cin.getline(name, 30);
                s1.updateData(name);
                cout << "\nStudent record updated successfully." << endl;
                break;
            }
            case 6: { // Exit the program
                cout << "\nThank you for using the Student Management System!" << endl;
                exit(0);
            }
            default: { // Invalid choice
                cout << "\nInvalid input! Please try again." << endl;
                break;
            }
        }
        cout << "\nPress any key to return to the main menu..." << endl;
   
    }

    return 0;
}
