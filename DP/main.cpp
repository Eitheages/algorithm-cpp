#include "SingleString.h"
#include "Matrix.h"
#include "DoubleString.h"

int main() {
    string s = "axc", t = "ahbgdc";
    C::Solution *p = new C::Solution;
    int res = p->isSubsequence(s, t);
    cout << res << endl;
    return 0;
}