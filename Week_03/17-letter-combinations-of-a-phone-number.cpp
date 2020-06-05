class Solution {
public:
    void helper(string combination, unordered_map<int, string>& sets, 
                string digits, int i) {
        if (i == digits.length()) {
            ans.push_back(combination);
        }
        string s = sets[digits[i] - '0'];
        for (char c : s) {
            helper(combination + c, sets, digits, i + 1);
        }
    }

    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return ans;
        unordered_map<int, string> sets;
        sets[2] = "abc";
        sets[3] = "def";
        sets[4] = "ghi";
        sets[5] = "jkl";
        sets[6] = "mno";
        sets[7] = "pqrs";
        sets[8] = "tuv";
        sets[9] = "wxyz";
        string combination;
        helper(combination, sets, digits, 0);
        return ans;
    }

private:
    vector<string> ans;
};
