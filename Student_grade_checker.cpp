//student management System.
//all header files
#include<iostream>
#include<conio.h>
#include<string.h>
#include<iomanip>
#include<windows.h>
#include<fstream>
#include<stdlib.h>
#include<stdio.h>
#include<string>
#include<vector>
#include<unordered_map> 

using namespace std;


struct GradePolicy{
   int LowerBound;
   int UpperBound;
   char Grade;
};


class Courses{
    
    public:
    char Course_code[10];
    int credits;
    char Course_name[10];

   // constructor
   
    Courses(){
        strcpy(Course_code,"N/A");
        credits=0;
    }

    Courses(const char* code, int cr, const char* name) {
        strcpy(Course_code, code);
        credits = cr;
        strcpy(Course_name, name);
    }

};



unordered_map<string,Courses> courseCatalog(){
        unordered_map<string, Courses> courseCatalog = {
        {"CS101", Courses{"CS101", 4, "Data Structures"}},
        {"CS102", Courses{"CS102", 3, "Algorithms"}},
        {"CS103", Courses{"CS103", 3, "Operating Systems"}}
    };
    return courseCatalog;
    
}




class student
{
    char name[30];
    long long Roll_no;
    int age;
    char Branch[10];
    vector<string> registeredCourses;
    unordered_map<string,int> marks_map;
    double CGPA;
    

    string convert(string s)
    {
        for(int i=0;i<s.length();i++)
        {
            s[i]=toupper(s[i]);
        }
        return s;
    }

public:
    // void intro(void);   // introduction of project.
    void ccolor(int); //display colorful contain.
    // void loadingbar(void);   //simple loading bar.
    // void login(void); //simple login contain.
    void getdata(void);   //Get all data from user.
    void showdata(void);   //display all data .
    void viewAlldata();     //display all data from files.
    int storedata();        //store all data in a file
    void searchData(char *);    //search a perticuler data.
    void showsearch(void);      //display search.
    void deleteData(char *);    //delete a data.
    void updateData(char *);    //use to update a data.
    void Enter_courses(int);
    double Calculate_CGPA(const unordered_map<string, Courses>& courseCatalog);

    //constructor
    student()
    {
        Roll_no=0;
        age=0;
        CGPA=0.0;
        strcpy(Branch,"N/A");
        strcpy(name,"N/A");
    }




};
void student::ccolor(int clr){
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, clr);

//the above code displays colorful background.
}



// void student::login()
// {
//     ccolor(14); // simple login with user_id and password
//     char ui[]="ASHFAQUE";
//     char psw[]="3535";
//     char gui[10],gpsw[10];
//     cout<<"\n\t\t__"<<endl
//         <<"\t\t|ENTER USER ID:-|";
//     cin>>gui;
//     cout<<"\n\t\t__"<<endl
//         <<"\t\t|ENTER PASSWORD:-|";
//     cin>>gpsw;
//     if(strcmp(ui,gui)!=0 && strcmp(psw,gpsw)==0)
//        {
//            ccolor(12);
//         cout<<"\t\tINVALID UI AND PASSWORD:";
//         getch();
//         exit(0);
//     }
//     else
//     {
//         cout<<"\t\tLOGIN SUCSESSFULLY:-\n";
//     }
// }


void student::getdata()
{

   fflush(stdin);
   cout<<"\t* ENTER STUDENT NAME :";cin.getline(name,29);fflush(stdin);
   cout<<"\t* ENTER STUDENT ROLL.NO :";cin>>Roll_no;fflush(stdin);
   cout<<"\t* ENTER STUDENT AGE :";cin>>age;fflush(stdin);
   cout<<"\t*Enter Total registered courses by the student";
   int n;
   cin>>n;
   cout<<endl;
   Enter_courses(n);


}

void student::Enter_courses(int n){
    fflush(stdin);
    unordered_map<string,Courses> Temp=courseCatalog();

    while (n--) {
        string courseID;
        cout << "Enter the Course ID: ";
        cin >> courseID;
        if(Temp.find(courseID) == Temp.end()){
            cout<<"Course not Found"<<endl;
            n++;
        }
        else{
        registeredCourses.push_back(convert(courseID));
        cout << "Enter Marks obtained in " << courseID << ": ";
        cin >> marks_map[courseID];
        }
    }
}



double  student::Calculate_CGPA(const unordered_map<string, Courses>& courseCatalog) {
   vector<GradePolicy> gradePolicy = {
        {90, 100, 'A'}, {80, 89, 'B'}, {70, 79, 'C'},
        {60, 69, 'D'}, {50, 59, 'E'}, {0, 49, 'F'}
    };

    // Mapping grades to grade points
    unordered_map<char, int> gradePoints = {
        {'A', 10}, {'B', 8}, {'C', 6}, {'D', 4}, {'E', 2}, {'F', 0}
    };

    double totalGradePoints = 0.0;
    int totalCredits = 0;

    for (const auto& courseID : registeredCourses) {
        int marks = marks_map[courseID];
        char grade = 'F'; // Default grade

        // Determine the grade based on marks
        for (const auto& policy : gradePolicy) {
            if (marks >= policy.LowerBound && marks <= policy.UpperBound) {
                grade = policy.Grade;
                break;
            }
        }

        // Fetch the course credits
        if (courseCatalog.find(courseID) != courseCatalog.end()) {
            int credits = courseCatalog.at(courseID).credits;

            // Add grade points to total
            totalGradePoints += gradePoints[grade] * credits;
            totalCredits += credits;
        } else {
            cout << "Course ID " << courseID << " not found in catalog." << endl;
        }
    }

    // Calculate CGPA
    CGPA = (totalCredits > 0) ? (totalGradePoints / totalCredits) : 0.0;

    return CGPA;
}







void student::showdata()
{
    cout<<"\t|NAME of the student is       |->    "<<name<<"   "<<endl;
    cout<<"\t|                             |                   "<<endl;
    cout<<"\t|Roll.NO of the student is    |->       "<<Roll_no<<"          "<<endl;
           
    cout<<"\t|Age of the student is        |->        "<<age<<"         "<<endl;
    cout<<"\t|                             |                   "<<endl;
    cout<<"\t| Courses and marks of the students|-> ";
    if (marks_map.empty()) {
    cout << "marks_map is empty!" << endl;
   }
   else {
    for (const auto& it : marks_map) {
        cout << it.first << " -> " << it.second << endl;
    }
}   
        
}

int student::storedata()
{
    if(age==0 && Roll_no==0)
    {
        cout<<"\n Student data not initialized : ";
        return(0);
    }
    else
    {
        ofstream fout;
        fout.open("file.dat",ios::app|ios::binary);
        fout.write((char*)this,sizeof(*this));
        fout.close();
        return(1);

    }
}
void student::viewAlldata()
{
    ifstream fin;
    fin.open("file.dat",ios::in|ios::binary);
    if(!fin)
        cout<<"error file not found:";
    else{
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof()){
            showdata();
           fin.read((char*)this,sizeof(*this));
        }
        fin.close();
    }
}

void student::searchData(char *t)
{
    int count=0;
    ifstream fin;
    fin.open("file.dat",ios::in|ios::binary);
    if(!fin)
        cout<<"error file not found:";
    else{
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof()){
            if(!strcmp(t,name)){
                showdata();
                count++;
            }
           fin.read((char*)this,sizeof(*this));
        }
        if(count==0)
            cout<<"\n record not found:";
        fin.close();
    }
}
void student::showsearch()
{
    cout<<"\t\t*"<<"\n";
    cout<<"\t\t*                                   *"<<"\n";
    cout<<"\t\t*      STUDENT SEARCH OPTION        *"<<"\n";
    cout<<"\t\t*                                   *"<<"\n";
    cout<<"\t\t*"<<"\n";
    char ser[30];
    cout<<"\t\t Enter Name of the student:";
    fflush(stdin);
    cin.getline(ser,29);
    searchData(ser);
}
void student::deleteData(char *t)
{
     ifstream fin;
    ofstream fout;
    fin.open("file.dat",ios::in|ios::binary);
    if(!fin)
    {
        ccolor(12);
        cout<<"Error file not found:";
    }

    else{
        fout.open("temp.dat",ios::out|ios::binary);
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof())
        {
            if(strcmp(name,t))
                fout.write((char*)this,sizeof(*this));
            fin.read((char*)this,sizeof(*this));
        }
        fin.close();
        fout.close();
        remove("file.dat");
        rename("temp.dat","file.dat");
    }
}
void student::updateData(char *t)
{
    fstream file;
    file.open("file.dat",ios::in|ios::out|ios::ate|ios::binary);
    file.seekg(0);
    file.read((char*)this,sizeof(*this));
    while(!file.eof())
    {
        if(!strcmp(t,name)){
            getdata();
            file.seekp(file.tellp()-sizeof(*this));
            file.write((char*)this,sizeof(*this));
        }
        file.read((char*)this,sizeof(*this));
    }
}

int main()
{
    student s1;
    // s1.loadingbar();
    // s1.intro();
    // s1.login();
    s1.ccolor(929);
    int choice;
    while(choice!=6)
    {
        s1.ccolor(929);
        system("cls");
    cout<<"*"<<"\n";
    cout<<"***                                                           ***"<<"\n";
    cout<<"***              1. Insert Student record.                    ***"<<"\n";
    cout<<"***              2. View All Student record.                  ***"<<"\n";
    cout<<"***              3. Search Student record.                    ***"<<"\n";
    cout<<"***              4. Delete Student record.                    ***"<<"\n";
    cout<<"***              5. Update Student record.                    ***"<<"\n";
    cout<<"***              6. For Exit The Program.                     ***"<<"\n";
    cout<<"***                                                           ***"<<"\n";
    cout<<"*"<<"\n";
    cout<<"\n        Enter Your choice:";
    cin>>choice;
    switch(choice)
    {
    case 1:
        s1.getdata();
        s1.storedata();
        cout<<"\n\t\t Data is Successfully Stored:";
        getch();
        break;
    case 2:
        s1.viewAlldata();
        getch();
        break;
    case 3:
        s1.showsearch();
        getch();
        break;
    case 4:
        cout<<"\n\n Enter Student Name to delete a record:";
        char name[30];fflush(stdin);
        cin.getline(name,29);
        s1.deleteData(name);
        cout<<"\n\t\t Data is Successfully Deleted:";
        getch();
        break;
    case 5:
        cout<<"\n\n Enter Student Name to Update a record:";fflush(stdin);
        cin.getline(name,29);
        s1.updateData(name);
        cout<<"\n\t\t Data is Successfully Updated:";
        getch();
        break;
    case 6:
        s1.ccolor(558);
        cout<<"\n\t\t Thank You For using This Application:";
        cout<<"\n\t\t Enter Any Key To Exit:-";
        getch();
        exit(0);
        break;
    default:
        s1.ccolor(12);
        cout<<"Invalid Input Try Again:";
        getch();
        }
    }
    getch();
}
