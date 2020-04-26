// Created by Gal Toubul

#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;
typedef vector<int> VI;
typedef vector<vector<int>> VVI;
#define GRAY true
#define WHITE false

VVI Adj; // n * m mat for Adj list
vector<bool> color; // n + 1 size vector for marking the nodes as white/gray
VI d; // n + 1 size vector for nodes' distances from root

void bfs() {

    // initialize
    int root = Adj[0][0];
    queue<int> Q ;
    Q.push(root);
    d[root] = 0;
    color[root] = GRAY;

    // main loop
    while (!Q.empty()) {

        // for each node u at the queue
        int u = Q.front(); Q.pop();
        cout << "exploring " << u << "'s Adj list" << endl;

        // for each WHITE node v the Adj list of u
        for(int v : Adj[u - 1]) {
            if (color[v] != WHITE) continue;

            color[v] = GRAY;
            d[v] = d[u] + 1;
            Q.push(v);

            cout << "   pushing " << v << " to Q. v.d = " << d[v] << endl;
        }
    }
}

int main(){
    ios::sync_with_stdio(0);
    int n, m = 0;
    cout << "How many nodes do have at your tree?" << endl;
    cin >> n;
    color.assign(n + 1, WHITE);
    d.assign(n + 1, numeric_limits<int>::max());
    Adj.assign(n + 1, vector<int>());

    for (int i = 0; i < n; ++i) {
        cout << "How many nodes do have at at the Adj list of node " << i + 1 << " ?" << endl;
        cin >> m;
        Adj[i].assign(m + 1, 0);
        Adj[i][0] = i + 1;

        cout << "Please enter them" << endl;
        for (int j = 1; j < m + 1; ++j) {
            int node;
            cin >> node;
            Adj[i][j] = node;
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << Adj[i][0];
        for (int j = 1; j < Adj[i].size(); ++j) {
            cout << " -> " << Adj[i][j];
        }
        cout << endl;
    }

    bfs ();

    return 0;
}
