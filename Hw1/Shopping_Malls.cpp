/**
 * Southwestern Europe Regional Contest (SWERC) 2013 / Shopping Malls
 * Created by Gal Toubul
 *
 * Algorithm: the problem is finding the short path between 2 given nodes.
 * Thus, we can run Dijkstra from the start node. By that we will get the shortest paths from it to all other nodes.
 * Then we will trace the "parents route" from the end node till we will reach the start node.
 *
 * Time complexity: O(VlgV + E), Dijkstra
 * Space complexity: O(V^2) for the graph
 */

#include <bits/stdc++.h>
using namespace std;
typedef vector<int> VI;
typedef vector<double> VD;
typedef vector<vector<int>> VVI;
typedef vector<vector<double>> VVD;

VVI Adj; // n * m size 2D vector for Adj list
VVD W; // n * n size 2D vector for edges weight
VD d; // n size 1D vector for vertices' distances from s
VI p; // n size 1D vector for vertices' parents
map<int, tuple<int, int, int>> et; //entry table map for transforming between a node and its index

struct compareD {
    bool operator()(pair<int, int> const& a, pair<int, int> const& b)
    {
        return a.second > b.second;
    }
};

// Function to calculate distance
double distance(int a, int b)
{
    int x1, y1, z1, x2, y2, z2;
    tie(x1, y1, z1) = et[a];
    tie(x2, y2, z2) = et[b];
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(5*(z2 - z1), 2));
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, m;
    cin >> n >> m;

    Adj.assign(n, VI());
    W.assign(n, VD(n,INT_MAX));

    priority_queue<pair<int, int>, vector<pair<int, int>>, compareD> Q;

    for (int i = 0; i < n; ++i){
        int x, y ,z;
        cin >> z >> x >> y ;
        et[i] = make_tuple(x, y, z);
        W[i][i] = 0;
    }

    for (int i = 0; i < m; ++i) {
        int a, b;
        double w;
        string move;
        cin >> a >> b >> move;
        if (move == "lift"){
            W[a][b] = 1;
            W[b][a] = 1;
        }
        else if (move == "escalator"){
            W[a][b] = 1;
            W[b][a] = 3 * distance(a, b);
        }
        else{
            w = distance(a, b);
            W[a][b] = w;
            W[b][a] = w;
        }

        Adj[a].push_back(b);
        Adj[b].push_back(a);
    }

    int s;
    cin >> s;

    // DIJKSTRA
    while (s--){
        int start, end;
        cin >> start >> end;

        // INITIALIZE-SINGLE-SOURCE
        d.assign(n, INT_MAX);
        d[start] = 0;
        p.assign(n, -1);

        Q.push(make_pair(start, 0));

        while (!Q.empty()){
            int u = Q.top().first;
            Q.pop();
            for (auto v : Adj[u]){

                // RELAX
                if (d[v] > d[u] + W[u][v]){
                    d[v] = d[u] + W[u][v];
                    p[v] = u;
                    Q.push(make_pair(v, d[v]));
                }
            }
        }

        if (p[end] == start)
            cout << start << " " << end << endl;

            // trace the "parents route" from the end node till we will reach the start node
        else{
            cout << start << " ";
            int curr = end;
            vector<int> vec;
            while (p[curr] != start){
                vec.push_back(p[curr]);
                curr = p[curr];
            }
            reverse(vec.begin(), vec.end());
            for(auto& i : vec)
                cout << i << " ";
            cout << end << endl;
        }
    }
    return 0;
}
