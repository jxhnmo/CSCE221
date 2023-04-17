#include <iostream>
using namespace std;

struct Node{
    int val;
    Node *left, *right;
};

int numNodes(Node *root){
    if (root == nullptr)
        return 0;
    return 1 + numNodes(root->left) + numNodes(root->right);
}

int numLeaves(Node *root){
    if (root == nullptr){
        return 0;
    }
    else if (root->left == nullptr && root->right == nullptr){
        return 1;
    }
    else{
        return numLeaves(root->left) + numLeaves(root->right);
    }
}

int fullNodes(Node *root){
    if (root == nullptr){
        return 0;
    }
    else if (root->left == nullptr && root->right == nullptr){
        return fullNodes(root->left) + fullNodes(root->right);
    }
    else{
        return 1 + fullNodes(root->left) + fullNodes(root->right);
    }
}

int treeHeight(Node *root){
    if (root == nullptr){
        return 0;
    }
    else{
        int leftHeight = treeHeight(root->left);
        int rightHeight = treeHeight(root->right);
        return 1 + max(leftHeight, rightHeight);
    }
}

int maxSumPath(Node *root){
    if (root == nullptr){
        return 0;
    }
    else {
        
    }
}

int main()
{
    
    return 0;
}