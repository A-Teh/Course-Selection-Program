#include "student.h"
#include "Class.h"
#include <set>
#include <vector>
using namespace std;

//Constructors

Student::Student() {
    this->name = "";
    this->year = 1;
    this->credits = 0;
    this->creditsEnrolled = 0;
    this->classesPassed = BloomFilter();
}

Student::Student(string name, int _year, int credit) {
    this->name = name;
    this->year = _year;
    this->credits = credit;
    this->creditsEnrolled = 0;
    this->classesPassed = BloomFilter();
}

Student::~Student(){
}

//Getters

string Student::getName() {
    return this->name;
}

int Student::getYear() {
    return this->year;
}

int Student::getCredits(){
    return this->credits;
}

int Student::getCreditsEnrolled(){
    return this->creditsEnrolled;
}

BloomFilter* Student::getClassesPassed() {
    return &this->classesPassed;
}
vector<Class>* Student::getClassesEnrolled(){
    return &this->classesEnrolled;
}

//Setters

void Student::setName(string name) {
    this->name = name;
}

void Student::setYear(int creditsTaken) {
    if (creditsTaken < 30) {
        year = 1;
    }
    else if (creditsTaken < 60) {
        year = 2;
    }
    else if (creditsTaken < 90) {
        year = 3;
    }
    else {
        year = 4;
    }
}

void Student::setCredits(int credit) {
    this->credits = credit;
}

void Student::setClassesPassed(BloomFilter* ClassesTaken){
    this->classesPassed = *ClassesTaken;
}

//Methods

//          string name;
//         int year;
//         int credits;
//         int creditsEnrolled;
//         BloomFilter classesPassed;
//         vector<Class> classesEnrolled;

//Testing helper to print out info about student
void Student::toString(){
    cout<<this->name<<":  Year "<<this->year<<" Total Credits: "<<this->credits<<" Credits Enrolled: "<<this->creditsEnrolled<<" ClassesEnrolled: ";
    if(this->classesEnrolled.size()==0)
        cout<<"None"<<endl;
    else{
        for(int i=0; i<this->classesEnrolled.size();i++)
            cout<<this->classesEnrolled[i].getName()<<"-"<<this->classesEnrolled[i].getSessionNum()<<" ";
        
        cout<<endl;
    }
}

void Student::addClassPassed(Class* _class){
    this->classesPassed.insert(_class->getName());
}

void Student::addClassPassed(string _class){
    this->classesPassed.insert(_class);
}

bool Student::enroll(Class _class){
    
    //Check credits
    //Stops adding classes after 15 credits
    if(this->creditsEnrolled >= 15 || this->creditsEnrolled + _class.getCredits() > 19){
        return false;
    }

    //Check capacity
    if(_class.getEnrolled() >= _class.getCapacity())
        return false;
    
    // Check prereqs
    set<string>::iterator itr;
    
    for (auto preReq: _class.getPreReqs()){
        if(!this->classesPassed.query(preReq)){
            return false;
        }
    }

    //Check if classes that have been taken overlap
    
    if(classesPassed.query(_class.getName())){
        return false;
    }

     
    //Check classes being taken for overlap
    for(int i = 0; i < this->classesEnrolled.size(); i++){
        if(_class.getName() == this->classesEnrolled[i].getName()){
        return false;
        }
        if(_class.isMWF() == this->classesEnrolled[i].isMWF())
            if( (_class.getStartTime() <= this->classesEnrolled[i].getEndTime() && _class.getEndTime() >= this->classesEnrolled[i].getStartTime()) || (this->classesEnrolled[i].getStartTime() <= _class.getEndTime() && this->classesEnrolled[i].getEndTime() >= _class.getStartTime()) ){
                return false;
    }
    }
 
    // Check if can add student
    if(_class.addStudent()){
        this->classesEnrolled.push_back(_class);
        this->creditsEnrolled+=_class.getCredits();
        return true;
    }else{
        return false;
    }
    return false;
}

//takes in vector of students and flashsorts them from lowest credits to most
void Student::flashSort(vector<Student>* students) {
    int studentsSize = students->size();
    // Number of buckets
    int m = 100; 
    std::vector<std::vector<Student>> buckets(m);
    
    // Classification phase  push students into buckets
    for (int i = 0; i < studentsSize; ++i) {
        int bucketIndex = static_cast<int>(students->at(i).getCredits() / 10);
        buckets[bucketIndex].push_back(students->at(i));
    }
    
    // put the almost sorted students back into the original vector 
    int index = 0;
    for (int i = 0; i < m; ++i) {
        for (Student& student : buckets[i]) {
            (*students)[index++] = student;
        }
    }
    
    // comb through the students and ensure everything is sorted
    for (int i = 1; i < studentsSize; ++i) {
        Student key = (*students)[i];
        int j = i - 1;
        while (j >= 0 && (*students)[j].getCredits() > key.getCredits()) {
            (*students)[j + 1] = (*students)[j];
            j--;
        }
        (*students)[j + 1] = key;
    }
}

// int main(int argc, char*argv[]){
//     return 0;
// }
