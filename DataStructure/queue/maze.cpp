#include <bits/stdc++.h>
using namespace std;

class Maze
{
public:
    Maze(vector<vector<int>> &matrix): cont(matrix), size(matrix.size()), state(vector<vector<unsigned>>(size, vector<unsigned>(size,0))), step(vector<vector<int>>(size, vector<int>(size, INT_MAX))){}
    ~Maze() = default;

    void initialize();
    void solve(int i, int j, int cnt = 0);
    int getAns()const{return step.back().back();}

private:
    int size;
    vector<vector<int>> cont;
    vector<vector<unsigned>> state;
    vector<vector<int>> step;
};

void Maze::initialize()
{
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            unsigned tmp = 0;
            if (i > 0 && cont[i-1][j] == 1)
                tmp += 8;
            if (i+1 < size && cont[i+1][j] == 1)
                tmp += 4;
            if (j > 0 && cont[i][j-1] == 1)
                tmp += 2;
            if (j+1 < size && cont[i][j+1] == 1)
                tmp += 1;
            state[i][j] = tmp;
        }
    }
}

void Maze::solve(int i, int j, int cnt)
{
    if (cnt >= step[i][j])
        return;
    else
        step[i][j] = cnt;
    ++cnt;
    if (state[i][j] % 2)
        solve(i, j+1, cnt);
    if (state[i][j]/2 % 2)
        solve(i, j-1, cnt);
    if (state[i][j]/4 % 2)
        solve(i+1, j, cnt);
    if (state[i][j]/8 % 2)
        solve(i-1, j, cnt);
}

int main()
{
    vector<vector<int>> matrix = {
        {1,1,0,0,0,0,0,1,1,1},
        {0,1,0,1,1,1,1,1,0,0},
        {0,1,1,1,0,0,1,0,0,0},
        {0,0,1,0,0,0,1,0,0,0},
        {0,0,1,0,0,0,1,1,1,0},
        {0,1,1,0,0,0,1,0,0,0},
        {0,0,1,1,1,1,1,0,0,0},
        {0,0,1,0,0,1,0,0,0,0},
        {0,0,0,0,0,1,1,1,1,1},
        {0,0,0,0,0,1,0,0,1,1}
    };
    Maze maze(matrix);
    maze.initialize();
    maze.solve(0, 0);
    cout << maze.getAns() << endl;
}