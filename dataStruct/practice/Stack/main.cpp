#include <iostream>
#include "Stack.h"

int main(int argc, char **argv)
{
    Stack<int> *myStack = new linkStack<int>;
    for (int i = 0; i < 20; i++)
    {
        myStack->push(i);
    }
    while (!myStack->isEmpty())
        std::cout<<myStack->pop()<<std::endl;
    return 0;
}