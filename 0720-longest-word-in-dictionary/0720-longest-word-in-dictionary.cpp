class Solution {
public:
    string longestWord(vector<string>& words) {
        sort(words.begin(), words.end());

        unordered_set<string> built;
        string ans = "";

        for (string &word : words) {
            if (word.size() == 1 || built.count(word.substr(0, word.size() - 1))) {
                built.insert(word);
                if (word.size() > ans.size()) {
                    ans = word;
                }
            }
        }

        return ans;
    }
};