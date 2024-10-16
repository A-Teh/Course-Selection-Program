#include "Class.h"
using namespace std;

//Constructors

Class::Class(){
    this->name = "";
    this->sessionNum = 1;
    this->credits = 0;
    this->capacity = 0;
    this->enrolled = 0;
    this->MWF = false;
    this->startTime = 0;
    this->endTime = 0;
}

Class::Class(string _name, int session, int credit, int maximum, bool MonWedFri, int start, int end){
    this->name = _name;
    this->sessionNum = session;
    this->credits = credit;
    this->capacity = maximum;
    this->enrolled = 0;
    this->MWF = MonWedFri;
    this->startTime = start;
    this->endTime = end;
}

Class::Class(string _name, int session, int credit, int maximum, bool MonWedFri, int start, int end, set<string> preRequisites){
    this->name = _name;
    this->sessionNum = session;
    this->credits = credit;
    this->capacity = maximum;
    this->max_capacity = maximum;
    this->enrolled = 0;
    this->MWF = MonWedFri;
    this->startTime = start;
    this->endTime = end;
    this->preReqs = preRequisites;
}

Class::~Class(){
}

//Getters

string Class::getName(){
    return this->name;
}

int Class::getSessionNum(){
    return this->sessionNum;
}

int Class::getCredits(){
    return this->credits;
}

int Class::getCapacity(){
    return this->capacity;
}

int Class::getMaxCapacity(){
    return this->max_capacity;
}

int Class::getEnrolled(){
    return this->enrolled;
}

bool Class::isMWF(){
    return this->MWF;
}

int Class::getStartTime(){
    return this->startTime;
}

int Class::getEndTime(){
    return this->endTime;
}

set<string> Class::getPreReqs(){
    return preReqs;
}

//Setters

void Class::setName(string _name){
    this->name = _name;
}

void Class::setSessionNum(int session){
    this->sessionNum = session;
}

void Class::setCredits(int credit){
    this->credits = credit;
}

void Class::setCapacity(int cap){
    this->capacity = cap;
}

void Class::setMWF(bool boolean){
    this->MWF = boolean;
}

void Class::setStart(int time){
    this->startTime = time;
}

void Class::setEnd(int time){
    this->endTime = time;
}

void Class::setPreReqs(set<string> preRequisites){
    this->preReqs = preRequisites;
}

//Methods

void Class::addPreReq(string preRequisite){
    this->preReqs.insert(preRequisite);
}

//Attempt to add the student to this class
    //Returns true if successful, false if not.
bool Class::addStudent(){
    //Check if there is room
    if(this->enrolled >= this->max_capacity)
        //return false;

    //All conditions met, add student
    this->enrolled++;

    return true;
}

string Class::nameWithoutChars(){
    string nameWithoutChars = "";
    for(int i = 0; i < name.length(); i++){
        if(!isalpha(name[i])){
            nameWithoutChars += name[i];
        }
    }
    return nameWithoutChars;

}

//Testing helper to print out info about student
void Class::toString(){
    
    cout<<this->name<<"-"<<this->sessionNum<<" Credits: "<<this->credits<<" Capacity: "<<this->capacity;
    
        for(auto req: this->preReqs)
            cout<<" Prereqs: " << req <<" ";
        
        cout<<endl;
    
}
