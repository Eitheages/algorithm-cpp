#include "SingleString.h"


int main() {
    vector<int> nums = {7,1,5,3,6,4};
    Solution *p = new Solution;
    int res = p->maxProfit(nums);
    cout << res << endl;
    return 0;
}