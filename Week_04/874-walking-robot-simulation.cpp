class Solution {
public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        int dx[] = {0, 1, 0, -1};
        int dy[] = {1, 0, -1, 0};
        //          ^  ^  ^   ^
        // dir =    N  E  S   W (0, 1, 2, 3)
        int dir = 0;
        unordered_set<string> obs_set;
        for (int i = 0; i < obstacles.size(); i++) {
            string s = to_string(obstacles[i][0]) + '#' + to_string(obstacles[i][1]);
            obs_set.insert(s);
        }

        int euclid_max = 0;
        int x = 0;
        int y = 0;
        for (int cmd : commands) {
            if (cmd == -1) {
                dir = (dir + 1) % 4;
            }
            else if (cmd == -2) {
                dir = (dir + 3) % 4;
            }
            else {
                for (int i = 0; i < cmd; i++) {
                    string s = to_string(x + dx[dir]) + '#' + to_string(y + dy[dir]);
                    if (obs_set.find(s) != obs_set.end()) {
                        // cout << s << endl;
                        break;
                    }
                    x += dx[dir];
                    y += dy[dir];
                    euclid_max = max(euclid_max, x*x+y*y);
                }
            }
        }

        return euclid_max;
    }
};
