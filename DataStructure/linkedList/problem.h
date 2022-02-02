#ifndef PRO_1
#define PRO_1

#include "basic.h"

class Solution {
public:
    bool hasCycle(ListNode *head) {
        if (head==nullptr||head->next==nullptr) return false;
        ListNode *f = head, *s = head;
        while (f->next && f->next->next){
            f = f->next->next;
            s = s->next;
            if (f == s) break;
        }
        if (f==s) return true;
        else return false;
    }
    
    ListNode* mergeTwoLists1(ListNode* l1, ListNode* l2) {
        ListNode *dumpNode = new ListNode(-1);
        ListNode *cur = dumpNode;
        while (l1&&l2){
            if (l1->val<l2->val){
                cur->next = l1;
                l1 = l1->next;
                cur = cur->next;
            }else{
                cur->next = l2;
                l2 = l2->next;
                cur = cur->next;
            }
        }
        cur->next = l1==nullptr?l2:l1;
        return dumpNode->next;
        delete dumpNode;
    }
    ListNode* mergeTwoLists2(ListNode* l1, ListNode* l2){
        if (l1==nullptr) return l2;
        else if (l2==nullptr) return l1;
        if (l1->val<l2->val){
            l1->next = mergeTwoLists2(l1->next,l2);
            return l1;
        }else{
            l2->next = mergeTwoLists2(l1,l2->next);
            return l2;
        }
    }

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int number, pre=0;
        ListNode *dumpNode = new ListNode(-1), *t = dumpNode;
        while (l1&&l2){
            number = l1->val+l2->val+pre;
            pre = number/10;
            number = number%10;
            t->next = new ListNode(number);
            t = t->next;
            l1 = l1->next;
            l2 = l2->next;
        }
        ListNode *temp = l1==nullptr?l2:l1;
        while (temp){
            number = temp->val+pre;
            pre = number/10;
            number = number%10;
            t->next = new ListNode(number);
            t = t->next;
            temp = temp->next;
        }
        if (pre!=0) t->next = new ListNode(pre);
        return dumpNode->next;
    }

    Node *getTail(Node *head){
        while (head->next) head = head->next;
        return head;
    }
    Node* flatten(Node* head) {
        if (head==nullptr) return head;
        Node *p = head;
        while (p->child == nullptr) {
            p = p->next;
            if (p==nullptr) return head;
        }
        Node *tail = getTail(p->child);
        tail->next = p->next;
        if (p->next) p->next->prev = tail;
        p->next = p->child;
        p->next->prev = p;
        p->child = nullptr;
        return flatten(head);
    }
    
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == nullptr) return head;
        ListNode *f=head, *s = head, *t = head;
        int size = 0;
        while (t){
            t = t->next;
            size++;
        }
        k %= size;
        while (k--) f = f->next;
        while (f->next){
            f = f->next;
            s = s->next;
        }
        f->next = head;
        ListNode *res = s->next;
        s->next = nullptr;
        return res;
    }
};

#endif