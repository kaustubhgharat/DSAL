#include <iostream>
#include <vector>
using namespace std;

class Heap {
public:
    // Heapify function to maintain the Min-Heap property
    void heapify(vector<int>& h, int i, int n) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && h[left] < h[smallest]) {
            smallest = left;
        }
        if (right < n && h[right] < h[smallest]) {
            smallest = right;
        }
        if (smallest != i) {
            swap(h[i], h[smallest]);
            heapify(h, smallest, n);
        }
    }

    // Heap sort function using Min-Heap
    void heapSort(vector<int>& h) {
        int n = h.size();

        vector<int> sorted;
        int pass = 1;

        // Step 2: Extract elements from the heap one by one
        while (!h.empty()) {
            sorted.push_back(h[0]);  // Extract min
            h[0] = h.back();         // Move last to root
            h.pop_back();            // Remove last

            if (!h.empty()) {
                heapify(h, 0, h.size());
            }

            // Print heap after each pass
            cout << "Pass " << pass << ": ";
            for (int val : h) {
                cout << val << " ";
            }
            cout << endl;
            pass++;
        }

        h = sorted;  // Final sorted array
    }
};

int main() {
    Heap h;
    vector<int> arr;
    int n, value;

    cout << "Enter the number of elements: ";
    cin >> n;

    cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> value;
        arr.push_back(value);
    }

    // Build min heap
    for (int i = arr.size() / 2 - 1; i >= 0; i--) {
        h.heapify(arr, i, arr.size());
    }

    cout << "Min-Heap after heapify operation: ";
    for (int val : arr) {
        cout << val << " ";
    }
    cout << endl;

    cout << "After sorting:\n";
    h.heapSort(arr);

    cout << "Final sorted array: ";
    for (int val : arr) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}
