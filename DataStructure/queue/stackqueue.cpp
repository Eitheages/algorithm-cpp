#include <bits/stdc++.h>
using namespace std;

class MyQueue {
public:
    MyQueue() {}

    void push(int x) {
        instk.push(x);
    }

    int pop() {
        int res = peek();
        outstk.pop();
        return res;
    }

    int peek() {
        if (outstk.empty())
            poul();
        int res = outstk.top();
        return res;
    }

    bool empty() {
        return instk.empty() && outstk.empty();
    }
private:
    stack<int> instk, outstk;
    void poul()
    {
        while (!instk.empty())
        {
            int tmp = instk.top();
            instk.pop();
            outstk.push(tmp);
        }
    }
};