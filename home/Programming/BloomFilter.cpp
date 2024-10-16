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

//Empty constructor, sets all bits to 0

//Insert
    //Intake a string of the form (CLASS)(NUMBER)
        //Ex: CSC212
//query
    //Intake a string of form (CLASS)(NUMBER)
    //Return boolean
        //True if possibly in set
        //False if definintely not in set


//Static variable to hold size of bit array
int bitSize = 200;


//k=3 unique hash functions (subject to change)
    //Currently modeled after BloomFilter Geeks for Geeks code
int hash1(string value){
    int hash = 0;
    for(int i = 0; i < value.size(); i++){
        hash = (hash+5*(int)value[i])%bitSize;
    }
    // cout<<hash%bitSize<<endl;
    return hash%bitSize;
}

int hash2(string value){
    int hash = 0;
    for(int i = 0; i < value.size(); i++){
        hash = (hash+ ((int)value[i]*13+5))%bitSize;
    }
    // cout<<hash%bitSize<<endl;
    return hash%bitSize;
}

int hash3(string value){
    int hash = 0;
    for(int i = 0; i < value.size(); i++){
        hash = (int)(hash+pow((int)value[i],2))%bitSize;
    }
    // cout<<hash%bitSize<<endl;
    return hash%bitSize;
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

void BloomFilter::insert(string value){
    // cout<<value<<endl;
    //Sets k bits to 1 based on the k unique hash functions
    this->bits[hash1(value)]=1;
    this->bits[hash2(value)]=1;
    this->bits[hash3(value)]=1;
}

bool BloomFilter::query(string value){
    //Checks if any of k bits are equal to 0 then value is not in the set
    if(this->bits[hash1(value)]==0
    || this->bits[hash2(value)]==0
    || this->bits[hash3(value)]==0)
        return false;    //Value is definitely not in set
    else
        return true;   //Value is possibly in set
}
