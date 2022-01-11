#include "Polynomial.h"

int main(int argc, char** argv)
{
    int a[3][2] = {{1,0}, {2,1}, {3,2}};
    int b[4][2] = {2,0,-2,1,5,2,1,3};
    Polynomial p1(2,a);
    Polynomial p2(3,b);
    std::cout << p1+p2 << std::endl;
}