#include <iostream>
using namespace std;

struct Node{
    int val;
    Node *left, *right;
};

void recur(int x){
    if (x > 0){
        recur(--x);
        cout << x << " ";
        recur(--x);
    }
}

int maxSumPath(Node* root){
    if (root == nullptr){
        return 0;
    }
    else{
        return root->val + max(maxSumPath(root->left), maxSumPath(root->right));
    }
}

int main(){
    return 0;
}