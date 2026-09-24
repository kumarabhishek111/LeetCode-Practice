class Solution {
    public int smallestIndex(int[] nums) { // Fixed method name
        for (int i = 0; i < nums.length; i++) {
            int digitSum = 0;
            int temp = nums[i];
            
            while (temp > 0) {
                digitSum += temp % 10;
                temp /= 10;
            }
            
            if (digitSum == i) {
                return i;
            }
        }
        return -1;
    }
}
