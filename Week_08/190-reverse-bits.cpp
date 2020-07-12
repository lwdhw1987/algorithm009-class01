class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t ans = 0;
        while (n) {
            uint32_t x = n & (-n);
            uint32_t i = log2(x);
            ans = ans | (1 << (31 - i));
            n = n & (n - 1);
        }

        return ans;
    }
};
