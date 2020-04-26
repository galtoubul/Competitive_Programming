// Created by Gal Toubul

#include <iostream>
#include <vector>
#include <string>
using namespace std;
typedef vector<int> VI;
typedef vector<vector<int>> VVI;
#define GRAY true
#define WHITE false

VVI Adj; // n * m mat for Adj list
vector<bool> color; // n + 1 size vector for marking the nodes as white/gray

void DFS(int node){
    color[node] = GRAY;

    cout << "exploring " << node << "'s Adj list" << endl;
    for(int j = 1; j < Adj[node - 1].size(); j++) {
        int u = Adj[node - 1][j];
        if(color[u] != WHITE){
            cout << "       node " << u << " was already visited" << endl;
            continue;
        }

        cout << "   calling DFS on node " << u << endl;
        DFS(u);
    }
}

int main(){
    ios::sync_with_stdio(0);
    int n, m = 0;
    cout << "How many nodes there are at your tree?" << endl;
    cin >> n;

    color.assign(n + 1, WHITE);
    Adj.assign(n, vector<int>());

    for (int i = 0; i < n; ++i) {
        cout << "How many nodes there are at the Adj list of node " << i + 1 << " ?" << endl;
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

    DFS(1);

    return 0;
}
