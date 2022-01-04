#include "basic.h"
#include "problem.h"
using namespace std;

inline void show(vector<int> vec){
    for (int i=0;i<vec.size();++i) printf("%-3d",vec[i]);
    printf("\n");
}

int main(){
    Solution solu;
    vector<int> a = {0,0,0,1,1,1,2,3,4,4,5,5,6,6,6,6};
    cout<<solu.removeDuplicates(a)<<endl;
    show(a);
    return 0;
}