#include <vector>

using namespace std;

class Solution {
public:
  int merge(vector<int> &nums, int left, int mid, int right, vector<int> &aux) {
    int res = 0, l = left, r = mid, flag = left;
    while (l < mid && r < right) {
      if (nums[l] <= nums[r]) {
        aux[flag++] = nums[l];
        res += r - mid;
        l++;
      } else {
        aux[flag++] = nums[r];
        r++;
      }
    }
    while (l < mid) {
      aux[flag++] = nums[l];
      res += r - mid;
      l++;
    }
    while (r < right) {
      aux[flag++] = nums[r];
      r++;
    }
    for (int i = left; i < right; i++) {
      nums[i] = aux[i];
    }
    return res;
  }
  int merge_sort(vector<int> &nums, int left, int right, vector<int> &aux) {
    if (right - left <= 1) {
      return 0;
    }
    int mid = (left) + (right - left) / 2;
    return merge_sort(nums, left, mid, aux) +
           merge_sort(nums, mid, right, aux) +
           merge(nums, left, mid, right, aux);
  }
  int reversePairs(vector<int> &nums) {
    vector<int> aux(nums.size(), 0);
    return merge_sort(nums, 0, nums.size(), aux);
  }
};