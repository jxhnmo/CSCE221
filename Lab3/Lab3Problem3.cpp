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

void intersection(List ListOne, List ListTwo){
    Node* L1 = ListOne.head;
    Node* L2 = ListTwo.head;
    List L3;
    
    while (L1 != nullptr && L2 != nullptr){
        if (L1 -> value < L2 -> value){
            L1 = L1 -> next;
        }
        else if (L1 -> value > L2 -> value){
            L2 = L2 -> next;
        }
        else{
            L3.append(L1 -> value);
            L1 = L1 -> next;
            L2 = L2 -> next;
        }
    }
};

void removeNode(Node* current){
    Node *removedNode = current -> next;
    current -> next = removedNode->next;
    current -> value = removedNode -> value;
    delete removedNode;
}

int main(){
    List ListOne;
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

    ListOne.head = P1;

    List ListTwo;
    Node* L1 = new Node();
    Node* L2 = new Node();
    Node* L3 = new Node();
    Node* L4 = new Node();

    L1->value = 1;
    L1->next = L2;

    L2->value = 3;
    L2->next = L3;

    L3->value = 4;
    L3->next = L4;

    L4->value = 7;

    ListTwo.head = L1;

    intersection(ListOne, ListTwo);

}