#include <iostream>
using namespace std;

int main(int argc, char**argv)
{
    int n;
    int* array;
    int ans1, ans2;
    while (cin >> n)
    {
        ans1 = ans2 = 0;
        array = new int[n+1];

        for (int i = 1; i <= n; i++)
            cin >> array[i];

        for (int i = 1; i <= n; i++)
        {
            if (array[i] != i)
            {
                int j = array[i], cnt = 1; // cnt record the length of the circle
                while (j != i)
                {
                    swap(array[i], array[j]);
                    j = array[i];
                    cnt++;
                }
                ans1 += (cnt - 1);
                ans2 = (ans2 == 2 || cnt > 2)? 2: 1;
            }
        }

        cout << ans1 << endl << ans2 << endl;
        delete []array;
    }
    return 0;
}