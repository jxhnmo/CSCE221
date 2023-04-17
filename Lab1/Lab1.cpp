#include <iostream>
#include <chrono>
using namespace std;

void fragment1(int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            sum = sum + i + j;
        }
    }
}

void fragment2(int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 2 * i; j++)
        {
            sum = sum + i + j;
        }
    }
}

int main()
{
    int n;
    cout << "Enter a value for n: ";
    cin >> n;

    auto time1 = chrono::high_resolution_clock::now();
    fragment1(n);

    auto time2 = chrono::high_resolution_clock::now();
    fragment2(n);

    auto time3 = chrono::high_resolution_clock::now();

    auto duration1 = chrono::duration_cast<chrono::nanoseconds>(time2 - time1);
    auto duration2 = chrono::duration_cast<chrono::nanoseconds>(time3 - time2);

    cout << "n value: " << n << "\nFrament 1 time: " << duration1.count() << " nanoseconds.\nFragment 2 time: " << duration2.count() << " nanoseconds.\n";
}
