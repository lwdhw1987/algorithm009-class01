class Solution {
public:
    int minMutation(string start, string end, vector<string>& bank) {

        unordered_set<string> bankSet(bank.begin(), bank.end());
        string gene = "ACGT";

        queue<string> bfs;
        unordered_set<string> visited;
        bfs.push(start);

        // BFS遍历，每次变换一个字符，查询是否在bank中，遇到目标停止
        int length = 1;
        while (!bfs.empty()) {
            int size = bfs.size();
            for (int i = 0; i < size; i++) {
                string s = bfs.front();
                bfs.pop();
                for (int j = 0; j < s.size(); j++) {
                    string ss = s;
                    for (char c : gene) {
                        ss[j] = c;
                        if (!bankSet.count(ss)) {
                            continue;
                        }

                        if (ss == end) {
                            return length;
                        }

                        if (!visited.count(ss)) {
                            bfs.push(ss);
                            visited.insert(ss);
                        }
                    }
                }
            }
            length++;
        }

        return -1;
    }
};
