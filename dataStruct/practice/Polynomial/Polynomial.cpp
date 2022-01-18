#include "Polynomial.h"

Polynomial::Polynomial(int n, int a[][2]): maxexp(n), head(new Node)
{
    // head points a dump node
    // initialize by, for example, a 2D array {{1,1}, {1,1}, {1,2}}
    Node* t = head;
    for (int i = 0; i <= n; i++)
    {
        t->next = new Node(a[i][0], a[i][1]); //a[i][1] is suppose to be i
        t = t->next;
    }
}

Polynomial::Polynomial(int n, Node* t_head): maxexp(n), head(t_head){}

Polynomial::Polynomial(const Polynomial& source): maxexp(source.maxexp), head(new Node)
{
    Node* t = head;
    Node* t_source = source.head;
    while (t_source->next)
    {
        Node* temp = t_source->next;
        t->next = new Node(temp->coef, temp->exp);
        t = t->next;
        t_source = temp;
    }
}

Polynomial::Polynomial(Polynomial &&source): maxexp(source.maxexp), head(new Node)
{
    head->next = source.head->next;
    source.head->next = nullptr;
}

Polynomial::~Polynomial()
{
    Node* t = head, *pre;
    do
    {
        pre = t;
        t = t->next;
        delete pre;
    } while (t);
}

std::ostream &operator<<(std::ostream &os, const Polynomial &obj)
{
    Polynomial::Node* t = obj.head;
    if (t->next == nullptr)
    {
        os << "No storage!";
        return os;
    }
    while (t->next)
    {
        t = t->next;
        if (t->exp == 0)
            os << t->coef;
        else if (t->coef > 0)
        {
            os << " + ";
            if (t->coef == 1)
                os << "x^" << t->exp;
            else
                os << t->coef << "x^" << t->exp;
        }
        else if (t->coef < 0)
        {
            os << " - ";
            if (t->coef == -1)
                os << "x^" << t->exp;
            else
                os << (-t->coef) << "x^" << t->exp;
        }
        
    }
    return os;
}

Polynomial operator+(const Polynomial &p1, const Polynomial &p2)
{
    int maxexp = p1.maxexp > p2.maxexp? p1.maxexp: p2.maxexp;
    Polynomial::Node* t1 = p1.head, *t2 = p2.head,
                    * res_head = new Polynomial::Node, *t = res_head;
    while (t1->next && t2->next)
    {
        t1 = t1->next;
        t2 = t2->next;
        t->next = new Polynomial::Node(t1->coef + t2->coef, t1->exp);
        t = t->next;
    }
    while (t1->next)
    {
        t1 = t1->next;
        t->next = new Polynomial::Node(t1->coef, t1->exp);
        t = t->next;
    }
    while (t2->next)
    {
        t2 = t2->next;
        t->next = new Polynomial::Node(t2->coef, t2->exp);
        t = t->next;
    }
    
    return Polynomial(maxexp, res_head);
}