#include <iostream>

int n, m;

inline int locate(int start, bool &dire, int live, int gap)
{
    int end;
    if (dire)
    {
        if (gap < live-start)
            end = start + gap;
        else if (gap < 2*live - start - 1)
        {
            end = 2*live - start - gap;
            dire = 0;
        }
        else
            end = 2 + gap + start - 2*live;
    }
    else
    {
        if (gap < start - 1)
            end = start - gap;
        else if (gap < live + start - 2)
        {
            end = 2 + gap - start;
            dire = 1;
        }
        else
            end = 2*live + start - gap - 2;
    }
    return end;
}

int solve(int start, bool dire, int live)
{
    if (live == 1)
        return 1;
    int gap = (m-1) % (2*live - 2);
    int end = locate(start, dire, live, gap);
    int p = dire? end: end-1;
    if (p == 1)
        dire = 1;
    else if (p == live - 1)
        dire = 0;
    int res = solve(p, dire, live-1);
    if (res < end)
        return res;
    else
        return res + 1;
}

int main()
{
    std::cin >> n >> m;
    std::cout << solve(1, 1, n) << std::endl;
    return 0;
}