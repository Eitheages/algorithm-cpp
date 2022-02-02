#include "LongLongInt.h"
using namespace std;

int main(int argc, char **argv)
{
    LongLongInt a;
    LongLongInt b;
    
    while (1)
    {
        cin >> a >> b;
        LongLongInt c = a + b;
        cout << c << endl;
    }

    return 0;
}