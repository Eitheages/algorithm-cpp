#include <bits/stdc++.h>
#include "problem.h"
#include "basic.h"
using namespace std;

int main(){
    int a[5] = {1,2,3,4,5};
    int b[4] = {3,4,5,6};
    int c[2] = {3,7};
    // MyLinkedList list;
    // for (int i=0;i<5;++i) list.addAtTail(a[i]);
    // list.show();
    Node *HeadA = new Node(a[0]);
    Node *HeadB = new Node(b[0]);
    Node *HeadC = new Node(c[0]);
    int i;
    Node *p;
    for (i=1,p=HeadA;i<5;++i){
        p->next = new Node(a[i],p);
        p = p->next;
    }
    for (i=1,p=HeadB;i<4;++i){
        p->next = new Node(b[i],p);
        p = p->next;
    }
    for (i=1,p=HeadC;i<2;++i){
        p->next = new Node(c[i],p);
        p = p->next;
    }
    HeadA->next->next->child = HeadB;
    HeadB->next->child = HeadC;

    Solution solu;
    Node *res = solu.flatten(HeadA);
    return 0;
}

/*
// 哈希表
public boolean hasCycle(ListNode head) {
        //记录表
        Set set = new HashSet();
        ListNode n = head;
        while (n != null) {
            if (set.contains(n)) return true;
            set.add(n);
            n=n.next;
        }
        return false;
    }

// 双指针
public boolean hasCycle(ListNode head) {
        ListNode slow=head,fast=head;
        while(slow!=null&&fast!=null){
            slow=slow.next;
            fast=fast.next==null?null:fast.next.next;
            if(slow!=null&&slow==fast)return true;
        }
        return false;
*/    