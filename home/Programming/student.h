//Creates a student object with a name, year, credits
#include <iostream>
#include <set>
#include <string>
#include "BloomFilter.h"
#include "Class.h"
#include <vector>

#pragma once

using namespace std;
class Student{
    public:
        //Constructors
        Student();
        Student(string name, int _year, int credit);
        ~Student();
        //Getters
        string getName();
        int getYear();
        int getCredits();
        int getCreditsEnrolled();
        BloomFilter* getClassesPassed();
        vector<Class>* getClassesEnrolled();
        //Setters
        void setName(string name);
        void setYear(int creditsTaken);
        void setCredits(int credit);
        void setClassesPassed(BloomFilter* ClassesTaken);
        //Methods
        void toString();
        void addClassPassed(Class* _class);
        void addClassPassed(string _class);
        bool enroll(Class _class);
        static void flashSort(vector<Student>* students); //sorts the students from least credits to most credits
    private:
        string name;
        int year;
        int credits;
        int creditsEnrolled;
        BloomFilter classesPassed;
        vector<Class> classesEnrolled;

        
};


