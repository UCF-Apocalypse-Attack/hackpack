/**
 * Author: Luke Videckis
 * Date: 2024-01-08
 * License: CC0
 * Source: https://github.com/lrvideckis/programming_team_code/
 * Description: Calls callback function on undirected forest for each centroid
 * Usage: centroid(adj, [\&](const vector<vector<int>>\& adj, int cent) { \ldots\ });
 * Time: $O(n \log n)$
 * Status: Untested
 */
#pragma once

template <class F> struct centroid {
    vector<vector<int>> adj;
    F f;
    vector<int> sub_sz;
    centroid(const vector<vector<int>>& a_adj, F a_f)
        : adj(a_adj), f(a_f), sub_sz(ssize(adj), -1) {
        for (int i = 0; i < ssize(adj); i++)
            if (sub_sz[i] == -1) dfs(i);
    }
    void calc_sz(int u, int p) {
        sub_sz[u] = 1;
        for (int v : adj[u])
            if (v != p)
                calc_sz(v, u), sub_sz[u] += sub_sz[v];
    }
    void dfs(int u) {
        calc_sz(u, -1);
        for (int p = -1, sz_root = sub_sz[u];;) {
            auto big_ch = find_if(begin(adj[u]), end(adj[u]), [&](int v) {
                return v != p && 2 * sub_sz[v] > sz_root;
            });
            if (big_ch == end(adj[u])) break;
            p = u, u = *big_ch;
        }
        f(adj, u);
        for (int v : adj[u]) {
            iter_swap(find(begin(adj[v]), end(adj[v]), u), rbegin(adj[v]));
            adj[v].pop_back();
            dfs(v);
        }
    }
};