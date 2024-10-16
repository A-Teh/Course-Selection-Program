// Implementation of the Range Tree. used for keeping all the classes that a student needs to take 
// Add all courses for Comp Sci B.S
// Order classes based on level from left to right 

#include "RangeTree.h"
#include <string>

using namespace std;

RTNode::RTNode(){
    this->data = 0; //Initializes data to be 0 
    this->perc_full = 0;
    this->name = "";
    this->left_ptr = nullptr;//left and right pointers null
    this->right_ptr = nullptr;
}

RTNode::RTNode(int data){
    this->data = data;//Makes data's member equal to argument
    this->left_ptr = nullptr; //Pointers equal nullpointer
    this->right_ptr = nullptr;
}

RTNode::RTNode(float perc_full, string name){
    this->perc_full = perc_full;
    this->name = name;
    this->left_ptr = nullptr; //Pointers equal nullpointer
    this->right_ptr = nullptr;
}

RTNode::~RTNode(){

}

RTree::RTree(){
    this->root = nullptr;
}

//Sets root to input data
RTree::RTree(int data){
    this->root = new RTNode(data);
}

//Destructor that just calls destroy
RTree::~RTree(){
    destroy();
}

//Private insert that does the recursive work for inserting
RTNode* RTree::insert(RTNode* root, float perc_full, string name){
    
    if(root == nullptr){
       return new RTNode(perc_full, name);
    }
   
    if(perc_full <= root->perc_full){
        root->left_ptr = insert(root->left_ptr, perc_full, name);
    }
    else if(perc_full > root->perc_full){
        root->right_ptr = insert(root->right_ptr, perc_full, name);
    }

    return root;
}

//Public method that calls private version
void RTree::insert(float perc_full, string name){
    this->root = insert(this->root, perc_full, name);
}

void RTree::preorder(RTNode* root, std::ostream& os){
    if(root == nullptr){
        return;
    }

    os << root->perc_full << ' ' ;

    preorder(root->left_ptr, os);

    preorder(root->right_ptr, os);

}
//Public version
void RTree::preorder(std::ostream& os){
    preorder(root, os);
}

void RTree::inorder(RTNode* root, std::ostream& os){
    if(root == nullptr){
        return;
    }

    inorder(root->left_ptr, os);

    os << root->perc_full << ' ';

    inorder(root->right_ptr, os);
}

//Public version
void RTree::inorder(std::ostream& os){
    inorder(root, os);
}

void RTree::postorder(RTNode* root, std::ostream& os){

    if(root == nullptr){
        return;
    }

    postorder(root->left_ptr, os);

    postorder(root->right_ptr, os);

    os << root->perc_full << ' ' ;

}

void RTree::postorder(std::ostream& os){
    postorder(root, os);
}

//Destroy everything from the ground up, this is called by the destructor
void RTree::destroy(RTNode* root){
  
    if(root != nullptr){
        destroy(root->left_ptr);
        destroy(root->right_ptr);
        delete root;
    }

}
//Public version
void RTree::destroy(){
    destroy(root);
    root = nullptr;
}

//Private Version
 RTNode* RTree::remove(RTNode* root, int data){
    if(root == nullptr){
        return root;
    }
    if(data < root->data){
        root->left_ptr = remove(root->left_ptr, data);
    } 
    else if( data > root->data){
        root->right_ptr = remove(root->right_ptr, data);
    }
    else{
        if(root->left_ptr == nullptr){
            RTNode* temp = root->right_ptr;
            delete root;
            return temp;
        } //Same as above but switched
        else if(root->right_ptr == nullptr){
            RTNode* temp = root->left_ptr;
            delete root;
            return temp;
        }
            RTNode* min = root->right_ptr;
            while (min->left_ptr != nullptr){
            min = min->left_ptr;
         }
        root->data = min->data;
        root->right_ptr = remove(root->right_ptr, min->data);

    }

  return root;

 }
//Public version
void RTree::remove(int data){
    root = remove(root, data);
}

bool RTree::search(int data) {
    return this->searchNode(this->root, data);
}

bool RTree::searchNode(RTNode* root, int data){

    if(root == nullptr){
        return false;
    }

    if(data == root->data){
        return true;
    } 
    else if(data < root->data){
        return searchNode(root->left_ptr, data);
    }
    else{
        return searchNode(root->right_ptr, data);
    }
}

std::vector<string> RTree::inRange(float low, float high) {
    std::vector<string> result;
    inRange(root, low, high, result);
    return result;
}

void RTree::inRange(RTNode* root, float low, float high, std::vector<string>& result) {
    if (root == nullptr)
        return;

    if (root->perc_full >= low && root->perc_full <= high) {
        result.push_back(root->name);
        inRange(root->left_ptr, low, high, result);
        inRange(root->right_ptr, low, high, result);
    }
    else if (root->perc_full < low) {
        inRange(root->right_ptr, low, high, result);
    }
    else {
        inRange(root->left_ptr, low, high, result);
    }
}


