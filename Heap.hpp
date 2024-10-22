#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Heap {
public:
    Heap() {
        heap = vector<int>();
    }
    Heap(vector<int>&& arr) {
        heap = arr;
        for (int i = (heap.size() - 1) >> 1; i >= 0; i--) minHeapify(i);
    }
    Heap(vector<int>&& arr, bool b) {
        heap = std::move(arr);
        for (int i = (heap.size() - 1) >> 1; i >= 0; i--) maxHeapify(i);
    }
    void MaxHeapify() {
        for (int i = (heap.size() - 1) >> 1; i >= 0; i--) maxHeapify(i);
    }
    void MinPush(int val) {
        int i = heap.size();
        heap.resize(heap.size() + 1);
        int x = val;
        int p = 0;
        for (; i > 0; i = p) {
            p = (i - 1) >> 1;
            if (heap[p] > x) {
                heap[i] = heap[p];
            } else {
                break;
            }
        }
        heap[i] = x;
    }
    void MaxPush(int val) {
        int i = heap.size();
        heap.resize(heap.size() + 1);
        int x = val;
        int p = 0;
        for (; i > 0; i = p) {
            p = (i - 1) >> 1;
            if (heap[p] < x) {
                heap[i] = heap[p];
            } else {
                break;
            }
        }
        heap[i] = x;
    }

    friend ostream& operator<<(ostream& os, const Heap& h) {
        for (int i = 0; i < h.heap.size(); i++) {
            os << h.heap[i] << " ";
            int t = i + 2;
            if ((t & (t - 1)) == 0) os << endl;
        }
        return os;
    }

    int ExtractMin() {
        int x = heap[0];
        swap(heap[0], heap[heap.size() - 1]);
        heap.pop_back();
        minHeapify(0);
        return x;
    }
private:
    void maxHeapify(int i) {
        int left = (i << 1) + 1;
        int right = left + 1;
        int x = heap[i];
        int maxIndex = left;
        while (left < heap.size()) {
            if (right >= heap.size()) right = left;
            if (heap[left] < heap[right]) maxIndex = right;
            if (heap[maxIndex] <= x) break;
            heap[i] = heap[maxIndex];
            i = maxIndex;
            left = (i << 1) + 1;
            right = left + 1;
            maxIndex = right;
        }
        heap[i] = x;
    }
    void minHeapify(int i) {
        int left = (i << 1) + 1;
        int right = left + 1;
        int x = heap[i];
        int minIndex = left;
        while (left < heap.size()) {
            if (right >= heap.size()) right = left;
            if (heap[left] > heap[right]) minIndex = right;
            if (heap[minIndex] >= x) break;
            heap[i] = heap[minIndex];
            i = minIndex;
            left = (i << 1) + 1;
            right = left + 1;
            minIndex = left;
        }
        heap[i] = x;
    }
    vector<int> heap;
};