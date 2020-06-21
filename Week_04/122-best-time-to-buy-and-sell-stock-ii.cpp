class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int buy = 0;
        int profit = 0;

        for (int i = 1; i < prices.size(); i++) {
            int daily = prices[i] - prices[i-1];
            if (daily > 0) {
                profit += daily;
            }
        }

        return profit;
    }
};
