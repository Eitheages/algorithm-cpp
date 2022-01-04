#ifndef basic_h
#define basic_h

#include <iostream>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;

    Node(int val, Node *prev=nullptr, Node* next = nullptr, Node *child = nullptr){
        this->val = val;
        this->prev = prev;
        this->next = next;
        this->child = child;
    }
};


class MyLinkedList {
public:
  
    MyLinkedList() {
        size = 0;
        // head 指向头节点，值无效
        head = new ListNode(0);
    }
    
    int get(int index) {
        if (index<0 || index>size-1) return -1;
        ListNode *pin = head->next;
        while (index--) pin = pin->next;
        return pin->val;
    }
    
    void addAtHead(int val) {
        ListNode *newnode = new ListNode(val);
        newnode->next = head->next;
        head->next = newnode;
        size++;
    }
    
    void addAtTail(int val) {
        ListNode *pin = head;
        while (pin->next) pin = pin->next;
        pin->next = new ListNode(val);
        size++;
    }
    
    void addAtIndex(int index, int val) {
        if (index>size) return;
        if (index<=0) {addAtHead(val);size++;return;}
        ListNode *pin = head;
        while (index--) pin = pin->next;
        ListNode *newnode = new ListNode(val);
        newnode->next = pin->next;
        pin->next = newnode;
        size++;
    }
    
    void deleteAtIndex(int index) {
        if (index<0 || index>size-1) return;
        if (index==0) {
            ListNode *temp = head->next;
            head->next = temp->next;
            delete temp;
        }else{
            ListNode *pin = head;
            while (index--) pin=pin->next;
            ListNode *temp = pin->next;
            pin->next = temp->next;
            delete temp;
        }
        size--;
    }
    void show();

private:
    ListNode *head;
    int size;
};

void MyLinkedList::show(){
    if (head->next == nullptr) return;
    ListNode *pin = head->next;
    while (pin){
        cout<<pin->val;
        pin=pin->next;
        cout<<(pin!=nullptr?'\t':'\n');
    }
}

#endif