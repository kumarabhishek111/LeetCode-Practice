class Solution {
    int n, k;
    Node[] tree;

    class Node {
        int product;
        int[] count;

        Node(int product, int[] count) {
            this.product = product;
            this.count = count;
        }
    }

    Node merge(Node a, Node b) {
        if (a == null) return b;
        if (b == null) return a;

        int[] count = new int[k];

        // Prefixes completely inside a
        for (int r = 0; r < k; r++) {
            count[r] += a.count[r];
        }

        // Prefixes that start in a and continue into b
        for (int r = 0; r < k; r++) {
            int newRemainder = (a.product * r) % k;
            count[newRemainder] += b.count[r];
        }

        int product = (a.product * b.product) % k;

        return new Node(product, count);
    }

    Node makeNode(int value) {
        int r = value % k;
        int[] count = new int[k];

        // The single element itself is a prefix
        count[r] = 1;

        return new Node(r, count);
    }

    void build(int[] nums, int index, int left, int right) {
        if (left == right) {
            tree[index] = makeNode(nums[left]);
            return;
        }

        int mid = (left + right) / 2;

        build(nums, index * 2, left, mid);
        build(nums, index * 2 + 1, mid + 1, right);

        tree[index] = merge(tree[index * 2], tree[index * 2 + 1]);
    }

    void update(int index, int left, int right, int pos, int value) {
        if (left == right) {
            tree[index] = makeNode(value);
            return;
        }

        int mid = (left + right) / 2;

        if (pos <= mid) {
            update(index * 2, left, mid, pos, value);
        } else {
            update(index * 2 + 1, mid + 1, right, pos, value);
        }

        tree[index] = merge(tree[index * 2], tree[index * 2 + 1]);
    }

    Node query(int index, int left, int right, int ql, int qr) {
        if (ql <= left && right <= qr) {
            return tree[index];
        }

        int mid = (left + right) / 2;

        if (qr <= mid) {
            return query(index * 2, left, mid, ql, qr);
        }

        if (ql > mid) {
            return query(index * 2 + 1, mid + 1, right, ql, qr);
        }

        Node a = query(index * 2, left, mid, ql, qr);
        Node b = query(index * 2 + 1, mid + 1, right, ql, qr);

        return merge(a, b);
    }

    public int[] resultArray(int[] nums, int k, int[][] queries) {
        this.n = nums.length;
        this.k = k;

        tree = new Node[4 * n];

        build(nums, 1, 0, n - 1);

        int[] result = new int[queries.length];

        for (int i = 0; i < queries.length; i++) {
            int index = queries[i][0];
            int value = queries[i][1];
            int start = queries[i][2];
            int x = queries[i][3];

            // Persistent update
            update(1, 0, n - 1, index, value);

            // Get nums[start ... n-1]
            Node ans = query(1, 0, n - 1, start, n - 1);

            result[i] = ans.count[x];
        }

        return result;
    }
}