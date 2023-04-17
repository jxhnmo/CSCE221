#include <iostream>
using namespace std;

void recur(int x)
{
    if (x > 0)
    {
        recur(--x);
        cout << x << " ";
        recur(--x);
    }
}

int main()
{
    recur(4);
    return 0;
}