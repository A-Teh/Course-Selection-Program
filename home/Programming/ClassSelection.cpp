#include "student.h"
#include "RangeTree.h"
#include "Class.h"
#include "BloomFilter.h"
#include <set>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <cstdlib>

using namespace std;

//  g++ BloomFilter.cpp Class.cpp ClassSelection.cpp student.cpp RangeTree.cpp -o prog && ./prog ClassData.csv StudentData.csv


//Make a set of the classes required for CSC

vector<Class> InputClasses(string file){
    vector<Class> classes; //Create empty set of classes
    string name;
    int session;
    int credit;
    int maximum;
    bool MonWedFri;
    int start;
    int end;
    
    string line;
    string entry;
    ifstream table;                // 1. Create instance
    table.open(file);                    // 2. Open the file
    if(table.fail()){                           //    Check open
        cerr << "Can't open file\n";
        return classes;
    }
    
    int columnCounter = 0;
    getline(table, line); //Clear title line
    while(std::getline(table, line)){           // 3. get a line of data from table, store in 'line'
        set<string> preReqs;
        stringstream streamline(line);
        
        while(std::getline(streamline, entry, ',')){  // 4. loop each "column" in 'line'. It will be stored into 'entry'
            
            
            switch (columnCounter){
                case 0:
                    name = entry;
                    break;
                case 1:
                    session = stoi(entry);
                    break;
                case 2:
                    credit = stoi(entry);
                    break;
                case 3: 
                    maximum = stoi(entry);
                    break;
                case 4:
                    if (entry == "MWT"){
                        MonWedFri = true;
                    } else {
                        MonWedFri = false;
                    }
                    break;
                case 5:
                    start = stoi(entry);
                    break;
                case 6:
                    end = stoi(entry);
                    break;
                case 7:
                    if (entry.substr(0, 1) == "\""){
                        std::string concatenated = entry;
                        std::string nextEntry;
                        while(std::getline(streamline, nextEntry, ',')){
                            concatenated = concatenated + "," + nextEntry;
                            if(nextEntry.substr(nextEntry.length()-1,1)=="\"")
                              break;
                        }
                        entry = concatenated.substr(1,concatenated.length()-2);
                    }
                    stringstream streamline(entry);
                    string course;
                    while(std::getline(streamline, course, ',')){
                        if (course.substr(0, 1) == " "){
                            course = course.substr(1, course.length()-1);
                        }
                        preReqs.insert(course);
                        }
            
                    break;
            }
            columnCounter++;
        }
        
        Class c = Class(name, session, credit, maximum, MonWedFri, start, end, preReqs);
        classes.push_back(c);
    
        
        
        columnCounter = 0;
    }    
    table.close();                                  // 5. Close the file
    return classes;
    }

vector<Student> InputStudents(string& file){
    vector<Student> students; //Create empty set of classes
    string name;
    int year;
    int credit;
    vector<string> classesTaken;
    set<string> preReqs;
    string line;
    string entry;
    ifstream table;                // 1. Create instance
    table.open(file);                    // 2. Open the file
    if(table.fail()){                           //    Check open
        cerr << "Can't open file\n";
        return students;
    }
    
    int columnCounter = 0;
    getline(table, line); //Clear title line
    while(std::getline(table, line)){           // 3. get a line of data from table, store in 'line'
        
        stringstream streamline(line);
        classesTaken = {};
        while(std::getline(streamline, entry, ',')){  // 4. loop each "column" in 'line'. It will be stored into 'entry'
            
            switch (columnCounter){
                case 0:
                    name = entry;
                    break;
                case 1:
                    year = stoi(entry);
                    break;
                case 2:
                    credit = stoi(entry);
                    break;
                case 3:
                    if (entry.substr(0, 1) == "\""){
                        std::string concatenated = entry;
                        std::string nextEntry;
                        while(std::getline(streamline, nextEntry, ',')){
                            concatenated = concatenated + "," + nextEntry;
                            if(nextEntry.substr(nextEntry.length()-1,1)=="\"")
                              break;
                        }
                        entry = concatenated.substr(1,concatenated.length()-2);
                        stringstream streamline(entry);
                        string course;
                        while(std::getline(streamline, course, ',')){
                            if (course.substr(0, 1) == " "){
                                course = course.substr(1, course.length()-1);
                            }
                            classesTaken.push_back(course);
                        }
                    } else {
                        classesTaken.push_back(entry);
                    }
                    break;
            }
            
            
            
            columnCounter++;
        }
        Student stud = Student(name, year, credit);
            for (auto course: classesTaken){
                stud.addClassPassed(course);
            }
        students.push_back(stud);
        columnCounter = 0;
    }    
    table.close();                                // 5. Close the file
    return students;
    }

    int OutputStudents(string file, vector<Student> students){
        std::ofstream output_file(file);
        string line = "";
        // Check if the file is open successfully
        if (!output_file.is_open()) {
            std::cerr << "Error: Could not open the output file." << std::endl;
            return 1; // Return an error code
        }

        //Title line
        output_file << "Student Name,Credits Enrolled,Classes Enrolled"<<endl;

        for (auto student: students){
            output_file << student.getName() << "," << student.getCreditsEnrolled() <<  ",\"";
            
             for (Class _class: *student.getClassesEnrolled()){
                //cout << _class.getName() << endl;
                line = line + (_class.getName() + "-" + to_string(_class.getSessionNum()) + ", ");
                
             }
            line = line.substr(0,line.length()-2);
            output_file << line;
            output_file << "\"" << endl;
            line = "";
        }
        output_file.close();

        return 0;
        
    }

//Console : g++ ClassSelection.cpp BloomFilter.cpp Class.cpp RangeTree.cpp student.cpp -o prog && ./prog ClassData.csv StudentData.csv

//Main file and code for class selection algorithm

int main(int argc, char*argv[]){
    //Input Args: class_file student_file output_file
    
    if(argc != 4 && argc != 3){
        cout<<"Invalid arguments. Must be of form (Class File) (Student File) (OPTIONAL: Output File)"<<endl;
        return 0;
    }


    //Input variables from terminal
    string class_file = argv[1];
    string student_file = argv[2];
    string output_file;
    if(argc == 4)
        output_file = argv[3];
    else
        output_file = "output.csv";

    
    vector<Class> classes = InputClasses(class_file);
    cout << "Classes imported" << endl;
    vector<Student> students = InputStudents(student_file);
    cout << "Students imported" << endl;
    
    
    //Sort students
    Student::flashSort(&students);

    //Test
    //students[students.size()-1].toString();
    srand(2);
    for (int i = students.size()-1; i >= 0; i--){
        //Proof of concept
        
        for (int j = 0; j < classes.size(); j++){
            int _rand = rand() % classes.size();
            if (students[i].enroll(classes[(j+_rand)%classes.size()])){
                //Create new methods to shorten and make code run faster
                students[i].setCredits(students[i].getCredits()+classes[(j+_rand)%classes.size()].getCredits());
                classes[(j+_rand)%classes.size()].setCapacity(classes[(j+_rand)%classes.size()].getCapacity()-1);
                classes[(j+_rand)%classes.size()].addStudent();
            } else {
                //cout << students[i].getName() << " did not enroll for " << classes[(j+_rand)%classes.size()].getName() << endl;
            }
            
        }
    }
for (int i = 0; i < 5; i++){
    //students[students.size()-i-1].toString();
    //classes[i].toString();
}

RTree RangeTree;
for (auto _class: classes){
    string full_name = _class.getName() + "-" + to_string(_class.getSessionNum());
    RangeTree.insert((ceil((1-((float)_class.getCapacity())/(_class.getMaxCapacity()))*10000)/100), full_name);
}

//RangeTree.preorder();

//cout << "test: " << RangeTree.inRange(0.0, 20.0)[0] << endl;
for (auto t:  RangeTree.inRange(100.0, 100.0)){
    cout << t << " is filled" << endl;
}

for (auto t:  RangeTree.inRange(0, 30.0)){
    cout << t << " is less than 30% filled" << endl;
}

    //Print Students names and credits
    
    for(auto _student: students){
        //s.toString();
        if (_student.getCreditsEnrolled() < 12){
            cout << _student.getName() << " only has " << _student.getCreditsEnrolled() << " credits" << endl;
        }
        
    }
    
    OutputStudents(output_file, students);


    //Student Class Testing
    // Student::Student(string name, int _year, int credit) {
        // Class::Class(string _name, int session, int credit, int maximum, bool MonWedFri, int start, int end){

    // Student newStudent = Student("Test Student", 2, 20);

    // Class testClass1 = Class("testClass1", 1, 4, 30, true, 1000, 1050);
    // Class testClass2 = Class("testClass2", 1, 4, 30, true, 1000, 1050);
    // Class testClass3 = Class("testClass3", 1, 4, 30, true, 1000, 1050);
    // Class testClass4 = Class("testClass4", 1, 4, 30, true, 1000, 1050);

    //------------

    
    

    //Make a range tree of the required classes and their prereqs

    //Only a concept as of now.  Need implementation of range tree to accuratly create its 
    //RangeTree CSC_Major_Classes(classes);

    //---------Testing for bloom filter----------//
/*
    BloomFilter filter;

    filter.insert("CSC212");
    filter.insert("CSC457");
    filter.insert("MTH180");
    filter.insert("CSC211");
    filter.insert("CSC200");
    filter.insert("MTH141");
    filter.insert("MTH142");
    filter.insert("CSC381");
    filter.insert("MTH352");

    for(int i = 0; i < 500; i++){
        // std::cout<<i<<std::endl;
        string s = "CSC"+to_string(i);
        if(filter.query(s)){
            //std::cout<<s<<std::endl;
        }
    }*/

    // std::cout<<filter.query(5)<<std::endl;
    // std::cout<<filter.query(23)<<std::endl;
    // std::cout<<filter.query(25)<<std::endl;
    //-------------------------------------------


    return 0;
}






//CSV Data Sheet: https://docs.google.com/spreadsheets/d/1jI8GPYNiYl3RG32Gg3XtiqZTRHWCT4nNX2sPyBZxOJA/edit?usp=sharing
    //Select between tabs at bottom
    //File>Download>Comma Separated Values(.csv)

//Command Line Arguments: "ClassDataFile" "StudentDataFile" "OutputFileName"
    //Directories to class data csv files and student data csv files
    //Output directory of output csv file

//Input data from CSV file containing data about classes being offered
    //Data: Class name (CSC212), Session Number, Credits, Capacity, MWF/TTh, TimeStart, TimeEnd, Prereqs
    //Times are converted to military and stored as ints
    //Ex: 3:30 PM becomes 1530

//Input from CSV file containing data about students to create a list of students
    //Data: Name, Year, Credits, Classes taken

//Sort the list of students using FlashSort based on year and Credits
    //Seniors>Juniors>Sophomores>Freshmen
        //Higher credits first

//Make range tree of classes that the student has not taken
    //Range tree organized from left to right based the level of the courses
    //prereqs should be to the left of the course 

//Assign classes based on need in the sorted order
    //Save student info to output CSV as you go
    //Requirements:
        //No student can take classes that overlap
        //Maximum credits a student can take is 19
        //All students must have at least 12 credits

//Print Errors
    //Full classes (Need more sessions)
    //Low enrollment classes (<30% full, too many sessions/poor scheduled time)
    //Students with not enough credits enrolled (<12 credits)

//Output to CSV file (.txt)
    //Name, classes to take comma separated
