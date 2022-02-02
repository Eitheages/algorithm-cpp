#include <bits/stdc++.h>
using namespace std;

bool isValid(string s) {
    stack<char> stk;
    for (const char& ch: s)
    {
        switch (ch)
        {
        case '(': case '[': case '{':
            stk.push(ch);
            break;
        case ')':
            if (!stk.empty() && stk.top() == '(')
                stk.pop();
            else
                return false;
            break;
        case ']': case '}':
            if (!stk.empty() && stk.top() == ch-2)
                stk.pop();
            else
                return false;
            break;
        }
    }
    return stk.empty();
}

int main(int argc, char **argv)
{
    string s = "()[]{}([])";
    cout << isValid(s) << endl;
    return 0;
}