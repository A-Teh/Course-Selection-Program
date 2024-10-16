// #include <iostream>
#include <string>
#include <bitset>
using namespace std;

#pragma once

//BloomFilter.h
//Garrett Kemper
//CSC212 Final Project
//  4/11/2024

class BloomFilter{
    public:
        BloomFilter();
        ~BloomFilter();
        void insert(string value);
        bool query(string value);
    private:
        bitset<200> bits;   //Must match bitsize variable in BloomFilter.cpp

};
