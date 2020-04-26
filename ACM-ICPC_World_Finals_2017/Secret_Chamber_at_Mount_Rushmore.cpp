// ACM-ICPC World Finals 2017/Secret Chamber at Mount Rushmore
// Created by Gal Toubul

#include <iostream>
#include <vector>
#include <string>
using namespace std;
typedef vector<int> VI;
typedef vector<bool> VB;
typedef vector<vector<int>> VVI;
typedef vector<vector<bool>> VVB;
#define GRAY true
#define WHITE false

VVI Adj; // n * m mat for Adj list
VB color; // 26 size vector for marking the nodes as white/gray
VVB reachable; // reachable[i][j] == true <-> there is a route from i to j

void DFS(int node, int startingNode){
    color[node] = GRAY;
    reachable[startingNode][node] = true;

    for(int j = 0; j < Adj[node].size(); j++) {
        int u = Adj[node][j];
        if(color[u] != WHITE) continue;

        DFS(u, startingNode);
    }
}

int main(){
    ios::sync_with_stdio(0);
    int m, n;
    cin >> m >> n;

    Adj.assign(26, VI());
    reachable.assign(26, VB(26, false));

    while (m--){
        char a, b;
        cin >> a >> b;
        Adj[a - 'a'].push_back(b - 'a');
    }

    // DFS for each letter i in order to check which letters are reachable from i
    for (int i = 0; i < 26; ++i){
        color.assign(26, WHITE);
        DFS(i, i);
    }

    while (n--){
        bool ans = true;
        string word1, word2;
        cin >> word1 >> word2;

        if (word1.length() != word2.length())
            ans = false;

        else{
            for (int i = 0; i < word1.length(); i++){
                if (!reachable[word1.at(i) - 97][word2.at(i) - 97])
                    ans = false;
            }
        }

        cout << (ans ? "yes" : "no") << endl;
    }
    return 0;
}
