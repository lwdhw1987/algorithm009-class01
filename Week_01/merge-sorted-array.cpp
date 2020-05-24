class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int p = m - 1;
        int q = n - 1;
        int tail = m + n - 1;
        while (p >= 0 && q >= 0) {
            nums1[tail--] = nums1[p] > nums2[q] ? nums1[p--] : nums2[q--]; 
        }

        for (int i = 0; i < q + 1; i++) {
            nums1[i] = nums2[i];
        }
    }
};
