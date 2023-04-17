#include <iostream>
#include <vector>
using namespace std;

struct Node{
    Node* next = nullptr;
    int value = 0;
};

class List{
    public:
        Node* head = nullptr;
};

void reverseList(List P){
    Node* pNode = P.head;
    Node* temp = nullptr;
    Node* prev = nullptr;
    while (pNode != nullptr){
        temp = pNode -> next;
        pNode -> next = prev;
        prev = pNode;
        pNode = temp;
    }
    pNode = prev;

    while(pNode != nullptr){
        cout << pNode -> value << endl;
        pNode = pNode -> next;
    }
};

int main(){
    List P;
    Node* P1 = new Node();
    Node* P2 = new Node();
    Node* P3 = new Node();
    Node* P4 = new Node();

    P1->value = 1;
    P1->next = P2;

    P2->value = 3;
    P2->next = P3;

    P3->value = 4;
    P3->next = P4;

    P4->value = 6;

    P.head = P1;

    reverseList(P);
}