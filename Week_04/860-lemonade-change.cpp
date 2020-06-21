class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        int coin_five = 0;
        int coin_ten = 0;

        for (int income : bills) {
            if (income == 5) {
                coin_five++;
            }
            if (income == 10) {
                if (coin_five == 0) {
                    return false;
                }
                coin_five--;
                coin_ten++;
            }
            if (income == 20) {
                if (coin_ten > 0 && coin_five > 0) {
                    coin_five--;
                    coin_ten--;
                }
                else if (coin_five >= 3) {
                    coin_five = coin_five - 3;
                }
                else {
                    return false;
                }
            }
        }

        return true;
    }
};
