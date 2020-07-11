#include<iostream>
#include<vector>

using namespace std;

class KthLargest {
public:
    vector<int> heap;
    int size, heap_maxsize;

    KthLargest(int k, vector<int>& nums) {
        size = 0;
        heap_maxsize = k;
        heap.push_back(-1);
        for (int i = 0 ; i < nums.size() ; i++) {
            this->add(nums[i]);
        }
    }

    int add(int val) {
        if (size < heap_maxsize) {
            heap.push_back(val);
            size++;
            up(size);
        } else if (heap[1] < val){
            heap[1] = val;
            down(1);
        }
        return heap[1];
    }

    void up(int location) {
        if ((location >> 1 > 0) && (heap[location >> 1] > heap[location])) {
            adjust(location >> 1, location);
            up(location >> 1);
        }
    }

    void down(int location) {
        if (((location << 1) + 1 <= size) && (heap[(location << 1) + 1] <= heap[(location << 1)]) && (heap[(location << 1) + 1] < heap[location]))
            adjust((location << 1) + 1, location);
        else if (((location << 1) == size) && (heap[(location << 1)] < heap[location]) || ((location << 1) + 1 <= size) && (heap[(location << 1) + 1] >= heap[(location << 1)]) && (heap[(location << 1)] < heap[location]))
            adjust((location << 1), location);
    }

    void adjust(int i, int j) {
        swap(heap[i], heap[j]);
        down(i);
    }
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */