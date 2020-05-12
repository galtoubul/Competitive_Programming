// Created by Gal Toubul

#include <bits/stdc++.h>
using namespace std;
typedef vector<int> VI;
typedef vector<vector<int>> VVI;

VVI Adj; // n * m size 2D vector for Adj list
VVI W; // n * n size 2D vector for edges weight
VI d; // n size 1D vector for vertices' distances from s
VI p; // n size 1D vector for vertices' parents
vector<bool> S; // n size 1D vector for tracking the vertices we have already visited

struct compareD {
    bool operator()(pair<int, int> const& a, pair<int, int> const& b)
    {
        return a.second > b.second;
    }
};

int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, m;
    cin >> n >> m;

    Adj.assign(n, VI());
    W.assign(n, VI(n,INT_MAX));
    d.assign(n, INT_MAX);
    p.assign(n, -1);

    priority_queue<pair<int, int>, vector<pair<int, int>>, compareD> Q;

    for (int i = 0; i < n; ++i)
        W[i][i] = 0;

    int s;
    cin >> s;
    d[s] = 0;
    Q.push(make_pair(s, 0));
    S.assign(n, false);

    for (int i = 0; i < m; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        W[a][b] = w;
        W[b][a] = w;
        Adj[a].push_back(b);
        Adj[b].push_back(a);
    }

    while (!Q.empty()){
        int u = Q.top().first;
        Q.pop();
        S[u] = true;
        for (auto v : Adj[u]){
            if (d[v] > d[u] + W[v][u]){
                d[v] = d[u] + W[v][u];
                p[v] = u;
                Q.push(make_pair(v, d[v]));
            }
        }
    }

    cout << "Vertex    d" << endl;
    for (int i = 0; i < n; i++)
        cout << i << "         " << d[i] << endl;

    return 0;
}
