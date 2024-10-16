#include <iostream>
#include <string>
#include <set>


using namespace std;

#pragma once

class Class {
    public:
    //Constructors
        Class();
        Class(string _name, int session, int credit, int maximum, bool MonWedFri, int start, int end);
        Class(string _name, int session, int credit, int maximum, bool MonWedFri, int start, int end, set<string> preRequisites);
        ~Class();
    //Getters
        string getName();
        int getSessionNum();
        int getCredits();
        int getCapacity();
        int getEnrolled();
        bool isMWF();
        int getStartTime();  
        int getEndTime();
        set<string> getPreReqs();
        int getMaxCapacity();
    //Setters
        void setName(string name);
        void setSessionNum(int sessionNum);
        void setCredits(int credits);
        void setCapacity(int cap);
        void setMWF(bool boolean);
        void setStart(int time);
        void setEnd(int time);
        void setPreReqs(set<string> preReqs);
    //Methods
        void addPreReq(string preReq);
        bool addStudent(); 
        string nameWithoutChars(); //returns the name of the class without preceding chars (CSC212 -> 212)
        void toString();

    private:
        string name;
        int sessionNum;
        int credits;
        int capacity;
        int max_capacity;
        int enrolled;
        bool MWF;
        int startTime;  //military time (1330 == 1:30) etc
        int endTime;
        set<string> preReqs;
        
       
};
