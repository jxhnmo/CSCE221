#include <iostream>
#include <assert.h>
using namespace std;


// TODO (student): implement binary search
// return -1 is key is not present in the subarray A[p...r]
// return the index if key is present in the subarray A[p...r]

int binarySearch(int* A, int p, int r, int key) {
    if (p > r){
        return -1;
    }
    else{
        int mid = (p + r) / 2;
        if (key == A[mid]){
            return mid;
        }
        else if (key > A[mid]){
            return binarySearch(A, mid + 1, r, key);
        }
        else{
            return binarySearch(A, p, mid - 1, key);
        }
    }
}

int main() {
    // Don't modify the main function
    int test[] = {3, 7, 10, 12, 34, 45, 45, 57, 100};
    int index = 0;
    for(int i = 0; i < 9; i++)
    {
        index = binarySearch(test, 0, 8, test[i]);
        assert(test[index] == test[i]);
    }
    index = binarySearch(test, 0, 8, -10);
    assert(index == -1);
    
    cout << "Tests passed." << endl;

    return 0;
}
