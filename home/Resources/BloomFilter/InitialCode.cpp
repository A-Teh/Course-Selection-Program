#include "BloomFilter.h"
#include <iostream>
#include <string>
#include <bitset>
#include <cmath>
using namespace std;

//BloomFilter.cpp
//Garrett Kemper
//CSC212 Final Project
//  4/11/2024

//  g++ ./Programming/ClassSelection.cpp ./Programming/BloomFilter.cpp -o prog && ./prog



/*
Initial code to implement a bloom filter and understand how it works. Only takes in integers
*/


//Static variable to hold size of bit array
int bitSize = 200;


//k=3 unique hash functions (subject to change)
int hash1(int value){
    return value%bitSize;
}

int hash2(int value){
    return ((value*32+17)%212)%bitSize;
}

int hash3(int value){
    return int (pow(value,3/2))%bitSize;
}

BloomFilter::BloomFilter(){
    //If bit sizes dont match, fix variable and output warning.
    if(bitSize != this->bits.size()){
        perror("[!] Error, bitSize in BloomFilter.cpp does not match bit array size in BloomFilter.h");
        bitSize = this->bits.size();
    }

    //Initializes bit array to all zeros
    for(int i = 0; i < bitSize; i++)
        this->bits[i]=0;
        
}

BloomFilter::~BloomFilter(){

}

void BloomFilter::insert(int value){
    //Sets k bits to 1 based on the k unique hash functions
    this->bits[hash1(value)]=1;
    this->bits[hash2(value)]=1;
    this->bits[hash3(value)]=1;
}

bool BloomFilter::query(int value){
    //Checks if any of k bits are equal to 0 then value is not in the set
    if(this->bits[hash1(value)]==0
    || this->bits[hash2(value)]==0
    || this->bits[hash3(value)]==0)
        return false;    //Value is definitely not in set
    else
        return true;   //Value is possibly in set
}


//--------------------------------------------------------------------------


#include <iostream>
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
        void insert(int value);
        bool query(int value);
    private:
        bitset<200> bits;

};
