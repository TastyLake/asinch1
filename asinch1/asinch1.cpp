#include <iostream>
#include <vector>
#include <future>
#include <algorithm>

using namespace std;

future<int> findMinIndexAsync(const vector<int>& arr, int start, int end) {
    promise<int> p;
    future<int> f = p.get_future();

    thread t([&, start, end, p = move(p)]() mutable { 
        int minIndex = start;
        for (int i = start + 1; i <= end; ++i) {
            if (arr[i] < arr[minIndex]) {
                minIndex = i;
            }
        }
        p.set_value(minIndex);
        });

    t.detach();

    return f; 
}


void selectionSortAsync(vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n - 1; ++i) {
     
        future<int> minIndexFuture = findMinIndexAsync(arr, i, n - 1);

    
        int minIndex = minIndexFuture.get();


       
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
        }
    }
}

int main() {
    vector<int> arr = { 64, 25, 12, 22, 11 };

    cout << "Исходный массив: ";
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;

    selectionSortAsync(arr);

    cout << "Отсортированный массив: ";
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}

