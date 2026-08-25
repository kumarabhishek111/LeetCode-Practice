class Solution {
public:
    int missingMultiple(vector<int>& nums, int k) {
        int multiple = k;

        while (find(nums.begin(), nums.end(), multiple) != nums.end()) {
            multiple += k;
        }

        return multiple;
    }
};