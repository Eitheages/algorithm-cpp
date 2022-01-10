#include "SingleString.h"


int main() {
    vector<int> nums = {8,6,4,3,3,2,3,5,8,3,8,2,6};
    Solution *p = new Solution;
    int res = p->maxProfit3(nums);
    cout << res << endl;
    return 0;
}