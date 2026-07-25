class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<vector<pair<int, int>>> adj(n);

        for (auto &it : flights) {
            adj[it[0]].push_back({it[1], it[2]});
        }

        vector<int> dist(n, INT_MAX);
        queue<pair<int, pair<int, int>>> q;

        q.push({0, {src, 0}});
        dist[src] = 0;

        while (!q.empty()) {
            auto it = q.front();
            q.pop();

            int stops = it.first;
            int node = it.second.first;
            int cost = it.second.second;

            if (stops > k)
                continue;

            for (auto &x : adj[node]) {
                int next = x.first;
                int price = x.second;

                if (cost + price < dist[next]) {
                    dist[next] = cost + price;
                    q.push({stops + 1, {next, dist[next]}});
                }
            }
        }

        return dist[dst] == INT_MAX ? -1 : dist[dst];
    }
};