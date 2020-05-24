class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int carry = 1;
        int n = digits.size();
        for (int i = n - 1; i >= 0; i--) {
            int d = (digits[i] + carry) % 10;
            carry = (digits[i] + carry) / 10;
            digits[i] = d;
        }
        if (carry) {
            digits[0] = 1;
            digits.push_back(0);
        }

        return digits;
    }
};
