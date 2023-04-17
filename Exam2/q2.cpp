#include <iostream>
using namespace std;

int recur(int x)
{
    if (x == 0)
        return 0;
    return (x % 10 + recur(x / 10));
}

int main()
{
    cout << recur(12);
    return 0;
}