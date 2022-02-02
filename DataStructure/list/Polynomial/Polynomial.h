#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>

class Polynomial
{
    friend std::ostream &operator<<(std::ostream&, const Polynomial&);
    friend Polynomial operator+(const Polynomial &p1, const Polynomial &p2);
    struct Node
    {
        int coef, exp; //coefficient and exponent
        Node *next;

        Node(): next(nullptr){}
        Node(int x, int y, Node *p = nullptr): coef(x), exp(y), next{p}{}
    };
public:
    Polynomial () = default;
    Polynomial (int, Node*);
    Polynomial (int, int [][2]);
    Polynomial (const Polynomial&);
    Polynomial (Polynomial &&);
    ~Polynomial ();

private:
    Node *head;
    int maxexp; // max exponent
};


#endif