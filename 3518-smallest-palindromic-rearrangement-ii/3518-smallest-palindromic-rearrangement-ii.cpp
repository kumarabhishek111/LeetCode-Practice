class Solution {
public:
    static const int LIMIT = 1000000;

    long long comb(int n, int r) {
        if (r < 0 || r > n) return 0;
        r = min(r, n - r);
        long long res = 1;

        for (int i = 1; i <= r; i++) {
            long long a = n - r + i;
            long long b = i;

            long long g = gcd(a, b);
            a /= g;
            b /= g;

            g = gcd(res, b);
            res /= g;
            b /= g;

            if (res > LIMIT) return LIMIT + 1;
            res *= a;
            if (res > LIMIT) return LIMIT + 1;
        }

        return res;
    }

    long long count(vector<int>& cnt) {
        long long ways = 1;
        int total = 0;

        for (int x : cnt) {
            if (x == 0) continue;
            ways *= comb(total + x, x);
            if (ways > LIMIT) return LIMIT + 1;
            total += x;
        }

        return ways;
    }

    string smallestPalindrome(string s, int k) {
        vector<int> freq(26), half(26);
        char mid = 0;
        int len = 0;

        for (char c : s) freq[c - 'a']++;

        for (int i = 0; i < 26; i++) {
            half[i] = freq[i] / 2;
            len += half[i];
            if (freq[i] % 2) mid = char('a' + i);
        }

        if (count(half) < k) return "";

        string left;

        for (int pos = 0; pos < len; pos++) {
            for (int c = 0; c < 26; c++) {
                if (half[c] == 0) continue;

                half[c]--;
                long long ways = count(half);

                if (ways >= k) {
                    left.push_back(char('a' + c));
                    break;
                } else {
                    k -= ways;
                    half[c]++;
                }
            }
        }

        string right = left;
        reverse(right.begin(), right.end());

        if (mid) return left + string(1, mid) + right;
        return left + right;
    }
};