class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size(), m = word2.size();

        vector<int> suf(n + 1, m);
        int j = m - 1;

        for (int i = n - 1; i >= 0; i--) {
            if (j >= 0 && word1[i] == word2[j]) j--;
            suf[i] = j + 1;
        }

        vector<int> ans;
        bool used = false;
        j = 0;

        for (int i = 0; i < n && j < m; i++) {
            if (word1[i] == word2[j]) {
                ans.push_back(i);
                j++;
            } else if (!used && suf[i + 1] <= j + 1) {
                used = true;
                ans.push_back(i);
                j++;
            }
        }

        if (j != m) return {};
        return ans;
    }
};