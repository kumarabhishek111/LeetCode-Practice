class Solution {
    public int largestOverlap(int[][] img1, int[][] img2) {
        
        int n = img1.length;
        
        int[][] count = new int[2 * n - 1][2 * n - 1];
        
        int ans = 0;

        // Try every possible shift
        for (int r1 = 0; r1 < n; r1++) {
            for (int c1 = 0; c1 < n; c1++) {
                
                if (img1[r1][c1] == 1) {
                    
                    for (int r2 = 0; r2 < n; r2++) {
                        for (int c2 = 0; c2 < n; c2++) {
                            
                            if (img2[r2][c2] == 1) {
                                
                                int dr = r2 - r1 + n - 1;
                                int dc = c2 - c1 + n - 1;
                                
                                count[dr][dc]++;
                                
                                ans = Math.max(ans, count[dr][dc]);
                            }
                        }
                    }
                }
            }
        }

        return ans;
    }
}