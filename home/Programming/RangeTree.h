#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>

using namespace std;


class RTNode{

    private:
        int data;
        float perc_full;
        string name;
        RTNode* left_ptr;
        RTNode* right_ptr;

    public:
        RTNode();
        RTNode(int data);
        RTNode(float perc_full, string name);
        ~RTNode();
        friend class RTree;
};


class RTree{

    private:
        RTNode* root;
        RTNode* insert(RTNode* root, float perc_full, string name);

        //traversals
        void preorder(RTNode* root, std::ostream& os);
        void inorder(RTNode* root, std::ostream& os);
        void postorder(RTNode* root, std::ostream& os);

        void destroy(RTNode* root);

        RTNode* remove(RTNode* root, int data);

        void inRange(RTNode* root, float low, float high, std::vector<string>& result);

    public:

        RTree();
        RTree(int data);
        ~RTree();

        void insert(float perc_full, string name);

        //traverals
        void preorder(std::ostream& os = std::cout);
        void inorder(std::ostream& os = std::cout);
        void postorder(std::ostream& os = std::cout);

        void destroy();

        bool search(int data);
        void remove(int data);
        bool searchNode(RTNode* root, int data);

        std::vector<string> inRange(float low, float high);
        
};
