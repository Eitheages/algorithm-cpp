#include "SingleString.h"
#include "Matrix.h"
#include "DoubleString.h"

int main() {
    vector<int> nums = {3,3,3,2,5};
    A::Solution *p = new A::Solution;
    int res = p->wiggleMaxLength(nums);
    cout << res << endl;
    return 0;
}