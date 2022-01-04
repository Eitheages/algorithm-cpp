#include "SingleString.h"

int main() {
    vector<vector<int>> matrix = {{2,2,-1}};
    Solution *p = new Solution;
    int res = p->maxSumSubmatrix(matrix, 3);
    cout << res;
}