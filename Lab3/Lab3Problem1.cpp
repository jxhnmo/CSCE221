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

void printLots(List L, List P){
    Node* lNode = L.head;
    Node* pNode = P.head;
    int lIndex = 0;

    while (pNode != nullptr){
        for (int i = lIndex; i < pNode -> value; i++){
            lNode = lNode -> next;
            lIndex++;
        }
        cout << lNode -> value << endl;
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
    List L;
    Node* L1 = new Node();
    Node* L2 = new Node();
    Node* L3 = new Node();
    Node* L4 = new Node();
    Node* L5 = new Node();
    Node* L6 = new Node();
    Node* L7 = new Node();
    Node* L8 = new Node();
    Node* L9 = new Node();
    Node* L10 = new Node();

    L1->value = 100;
    L1->next = L2;

    L2->value = 101;
    L2->next = L3;

    L3->value = 102;
    L3->next = L4;

    L4->value = 103;
    L4->next = L5;

    L5->value = 104;
    L5->next = L6;

    L6->value = 105;
    L6->next = L7;

    L7->value = 106;
    L7->next = L8;

    L8->value = 107;
    L8->next = L9;

    L9->value = 108;
    L9->next = L10;

    L10->value = 109;

    L.head = L1;

    printLots(L, P);

}