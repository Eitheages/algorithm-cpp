#ifndef Basic
#define Basic

#include <bits/stdc++.h>
using namespace std;

class Matrix{
public:
    vector<vector<int>> matrix;
    int m,n;
    void show();
    void addrow(vector<int>&, int);
    void clear();
};

inline void Matrix::show(){
    for (int i=0;i<matrix.size();++i){
        for (int j=0;j<matrix[0].size();++j) printf("%-4d", matrix[i][j]);
        cout<<endl;
    }
}

void Matrix::addrow(vector<int> &row, int i=-1){
    if (!matrix.empty()&&row.size()!=matrix[0].size()) return;
    if (i==-1) matrix.emplace_back(row);
    else matrix.insert(matrix.begin()+i, row);
}

inline void Matrix::clear(){
    matrix.erase(matrix.begin(), matrix.end());
}

#endif