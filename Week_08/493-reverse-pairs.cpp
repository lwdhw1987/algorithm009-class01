class Solution {
public:
    void merge(vector<int>& nums, int left, int mid, int right) {
        for (int i = left; i <= right; i++) {
            temp[i] = nums[i];
        }

        int i = left;
        int p1 = left;
        int p2 = mid + 1; 
        // 前后部分分别有序，合并
        while (p1 <= mid || p2 <= right) {
            if (p1 > mid || (p2 <= right && temp[p1] > temp[p2])) {
                nums[i++] = temp[p2++];
            }
            else {
                nums[i++] = temp[p1++];
            }
        }
    }

    int mergeSort(vector<int>& nums, int left, int right) {
        if (right <= left) {
            return 0;
        }

        int mid = left + (right - left) / 2;
        int count = mergeSort(nums, left, mid) + mergeSort(nums, mid + 1, right);
        // 在合并之前完成逆序对统计
        for (int i = left, j = mid + 1; i <= mid; i++) {
            while (j <= right && (long)nums[i] > 2 * (long)nums[j]) {
                j++;
            }
            count += j - (mid + 1); 
        }

        merge(nums, left, mid, right);

        return count;
    }

    int reversePairs(vector<int>& nums) {
        temp.resize(nums.size());
        return mergeSort(nums, 0, nums.size() - 1);
    }
private:
    vector<int> temp;
};
