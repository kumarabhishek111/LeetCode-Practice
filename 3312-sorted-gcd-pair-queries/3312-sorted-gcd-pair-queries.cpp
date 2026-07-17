class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int mx = *max_element(nums.begin(), nums.end());

        vector<int> freq(mx + 1, 0);
        for (int x : nums) freq[x]++;

        // cnt[g] = number of pairs having gcd exactly g
        vector<long long> cnt(mx + 1, 0);

        for (int g = mx; g >= 1; g--) {
            long long c = 0;
            for (int j = g; j <= mx; j += g)
                c += freq[j];

            cnt[g] = c * (c - 1) / 2;

            for (int j = g + g; j <= mx; j += g)
                cnt[g] -= cnt[j];
        }

        // prefix over gcd values
        vector<long long> pref(mx + 1, 0);
        for (int g = 1; g <= mx; g++)
            pref[g] = pref[g - 1] + cnt[g];

        vector<int> ans;
        ans.reserve(queries.size());

        for (long long q : queries) {
            int g = lower_bound(pref.begin() + 1, pref.end(), q + 1) - pref.begin();
            ans.push_back(g);
        }

        return ans;
    }
};