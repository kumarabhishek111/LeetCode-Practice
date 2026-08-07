#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    // Helper function to extract prime factors 2, 3, 5, 7 from a digit
    void get_factors(int d, int &ca, int &cb, int &cc, int &cd) {
        ca = cb = cc = cd = 0;
        while (d % 2 == 0) { ca++; d /= 2; }
        while (d % 3 == 0) { cb++; d /= 3; }
        while (d % 5 == 0) { cc++; d /= 5; }
        while (d % 7 == 0) { cd++; d /= 7; }
    }

public:
    string smallestNumber(string num, long long t) {
        // Step 1: Prime factorize t
        // Digits 1-9 can only supply prime factors 2, 3, 5, and 7.
        long long temp = t;
        int req_a = 0, req_b = 0, req_c = 0, req_d = 0;
        while (temp % 2 == 0) { req_a++; temp /= 2; }
        while (temp % 3 == 0) { req_b++; temp /= 3; }
        while (temp % 5 == 0) { req_c++; temp /= 5; }
        while (temp % 7 == 0) { req_d++; temp /= 7; }
        
        // If t has any prime factor > 7, it's impossible.
        if (temp > 1) return "-1";
        
        // Step 2: Precompute DP table for min digits needed for required powers of 2 and 3
        int dp[60][40];
        for (int i = 0; i < 60; i++) {
            for (int j = 0; j < 40; j++) {
                dp[i][j] = 1e9;
            }
        }
        dp[0][0] = 0;
        
        for (int i = 0; i < 60; i++) {
            for (int j = 0; j < 40; j++) {
                if (i == 0 && j == 0) continue;
                int res = 1e9;
                for (int d : {2, 3, 4, 6, 8, 9}) {
                    int c2 = (d == 2 || d == 6) ? 1 : (d == 4 ? 2 : (d == 8 ? 3 : 0));
                    int c3 = (d == 3 || d == 6) ? 1 : (d == 9 ? 2 : 0);
                    int pa = max(0, i - c2);
                    int pb = max(0, j - c3);
                    res = min(res, 1 + dp[pa][pb]);
                }
                dp[i][j] = res;
            }
        }
        
        // Step 3: Check if original num is already zero-free and valid
        int n = num.length();
        bool num_valid = true;
        int cur_a = 0, cur_b = 0, cur_c = 0, cur_d = 0;
        int z = n; // Index of first zero
        
        for (int i = 0; i < n; i++) {
            if (num[i] == '0') {
                if (num_valid) {
                    z = i;
                    num_valid = false;
                }
            } else if (num_valid) {
                int ca, cb, cc, cd;
                get_factors(num[i] - '0', ca, cb, cc, cd);
                cur_a += ca; cur_b += cb; cur_c += cc; cur_d += cd;
            }
        }
        
        if (num_valid && cur_a >= req_a && cur_b >= req_b && cur_c >= req_c && cur_d >= req_d) {
            return num;
        }
        
        // Compute prefix sums of factor counts before the first zero
        vector<int> pref_a(n + 1, 0), pref_b(n + 1, 0), pref_c(n + 1, 0), pref_d(n + 1, 0);
        for (int i = 0; i < min(n, z); i++) {
            int ca, cb, cc, cd;
            get_factors(num[i] - '0', ca, cb, cc, cd);
            pref_a[i + 1] = pref_a[i] + ca;
            pref_b[i + 1] = pref_b[i] + cb;
            pref_c[i + 1] = pref_c[i] + cc;
            pref_d[i + 1] = pref_d[i] + cd;
        }
        
        string ans = "";
        bool found = false;
        
        // Step 4: Try finding divergence point within length n
        int start_i = min(n - 1, z);
        for (int i = start_i; i >= 0; i--) {
            int start_d = (num[i] == '0') ? 1 : (num[i] - '0' + 1);
            for (int D = start_d; D <= 9; D++) {
                int d_a, d_b, d_c, d_d;
                get_factors(D, d_a, d_b, d_c, d_d);
                
                int rem_a = max(0, req_a - (pref_a[i] + d_a));
                int rem_b = max(0, req_b - (pref_b[i] + d_b));
                int rem_c = max(0, req_c - (pref_c[i] + d_c));
                int rem_d = max(0, req_d - (pref_d[i] + d_d));
                
                // Minimum digits required to cover remaining factors
                if (rem_c + rem_d + dp[rem_a][rem_b] <= n - 1 - i) {
                    ans = num.substr(0, i) + (char)('0' + D);
                    int curr_a = pref_a[i] + d_a;
                    int curr_b = pref_b[i] + d_b;
                    int curr_c = pref_c[i] + d_c;
                    int curr_d = pref_d[i] + d_d;
                    
                    // Greedily fill remaining digits with smallest valid choices
                    for (int p = i + 1; p < n; p++) {
                        for (int d_fill = 1; d_fill <= 9; d_fill++) {
                            int f_a, f_b, f_c, f_d;
                            get_factors(d_fill, f_a, f_b, f_c, f_d);
                            
                            int n_rem_a = max(0, req_a - (curr_a + f_a));
                            int n_rem_b = max(0, req_b - (curr_b + f_b));
                            int n_rem_c = max(0, req_c - (curr_c + f_c));
                            int n_rem_d = max(0, req_d - (curr_d + f_d));
                            
                            if (n_rem_c + n_rem_d + dp[n_rem_a][n_rem_b] <= n - 1 - p) {
                                ans += (char)('0' + d_fill);
                                curr_a += f_a;
                                curr_b += f_b;
                                curr_c += f_c;
                                curr_d += f_d;
                                break;
                            }
                        }
                    }
                    found = true;
                    break;
                }
            }
            if (found) break;
        }
        
        // Step 5: Expand string length if length n is insufficient
        if (!found) {
            // Target length must be at least max(n + 1, min_digits_needed_for_t)
            int min_len = max(n + 1, req_c + req_d + dp[req_a][req_b]);
            ans = "";
            ans.reserve(min_len);
            
            int curr_a = 0, curr_b = 0, curr_c = 0, curr_d = 0;
            for (int p = 0; p < min_len; p++) {
                for (int d_fill = 1; d_fill <= 9; d_fill++) {
                    int f_a, f_b, f_c, f_d;
                    get_factors(d_fill, f_a, f_b, f_c, f_d);
                    
                    int n_rem_a = max(0, req_a - (curr_a + f_a));
                    int n_rem_b = max(0, req_b - (curr_b + f_b));
                    int n_rem_c = max(0, req_c - (curr_c + f_c));
                    int n_rem_d = max(0, req_d - (curr_d + f_d));
                    
                    if (n_rem_c + n_rem_d + dp[n_rem_a][n_rem_b] <= min_len - 1 - p) {
                        ans += (char)('0' + d_fill);
                        curr_a += f_a;
                        curr_b += f_b;
                        curr_c += f_c;
                        curr_d += f_d;
                        break;
                    }
                }
            }
        }
        
        return ans;
    }
};