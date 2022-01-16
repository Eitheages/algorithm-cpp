#include "SingleString.h"
#include "Matrix.h"

int main() {
    vector<vector<int>> a{{0,0,0}, {0,1,0}, {0,0,0}};
    B::Solution *p = new B::Solution;
    int res = p->uniquePathsWithObstacles(a);
    printf("%d\n", res);
    return 0;
}