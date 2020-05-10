// Southwestern Europe Regional Contest (SWERC) 2016 / Balls and Needles
// Created by Gal Toubul
// Algorithm: after making 2 trees matching to corresponding balls and needles
// run DFS for each node which wasn't traversed yet and search for non trivial circles.
// It's known that a tree contains a circle iff a DFS run will find a back edge.
// Though, we will have to be careful not to consider a trivial circle as closed chain.
// For instance: (u,v) - (v,u) is a trivial circle.
// We will make sure not to mark trivial circles as closed chains by tracking the nodes' discovery times.
// By that, when finding a back edge, we will check if the difference at discovery times is greater or equal 2.
// Time complexity: O(V+E) since we will run a DFS for node which wasn't traversed yet.
// Space complexity: O(V+E) : Adj lists array - O(V + E) , entry tables maps - O(V), color array - O(V), discovery array - O(V)

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <map>
using namespace std;
typedef vector<int> VI;
typedef vector<vector<int>> VVI;
typedef vector<vector<vector<int>>> VVVI;
typedef vector<vector<bool>> VVB;
#define GRAY 1
#define WHITE 0
#define DIM3 0
#define DIM2 1

// implementing < operator for using find on map
bool operator<(tuple<int, int, int> ball1, tuple<int, int, int> ball2) {
    int x1, y1, z1, x2, y2, z2;
    tie(x1, y1, z1) = ball1;
    tie(x2, y2, z2) = ball2;

    if(x1 == x2) {
        if(y1 == y2)
            return z1 < z2;
        return y1 < y2;
    }
    return x1 < x2;
}

VVVI Adj; // O(2 * (100010 + m)) 3D mat for the Adj lists of 3 and 2 dimensions balls

// entry tables for transforming each ball(tuple<int, int, int>) to its corresponding index at the tree
map<tuple<int, int, int>, int> dim2Et, dim3Et;

int dim2LastInd, dim3LastInd; // current Last index (node's number) at the tree
VVI color; // (2 * 100010) 2D mat for marking the nodes as white/gray
VVI discovery; // (2 * 100010) 2D mat for the nodes' discovery time

vector<bool> closed; // flags to identify closed chains and floor closed chains

void DFS(int dim, int v, int d){
    color[dim][v] = GRAY;
    discovery[dim][v] = d;

    for(int j = 0; j < Adj[dim][v].size(); j++) {
        int u = Adj[dim][v][j];

         // color[dim][u] != WHITE iff (v,u) is a back edge
        if(color[dim][u] != WHITE){

            // diff of 1 may be the opposite direction edge -> not a closed chain
            if (discovery[dim][u] <= discovery[dim][v] - 2){
                closed[dim] = true;
                return;
            }

            continue;
        }

        // for each white node at the Adj list make a recursive call
        DFS(dim, u, d + 1);
    }
}

int main(){
    ios::sync_with_stdio(0);
    Adj.assign(2, VVI(100010));
    discovery.assign(2, VI(100010));
    color.assign(2, VI(100010));
    closed.assign(2, false);

    int K;
    cin >> K;
    while (K--)
    {
        int x1, y1, z1, x2, y2, z2;
        cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
        tuple<int, int, int> ball1 (x1, y1, z1);
        tuple<int, int, int> ball2 (x2, y2, z2);

        // check if the new balls weren't inserted earlier, and if not add new node's index for them
        if(dim3Et.find(ball1) == dim3Et.end())
            dim3Et[ball1] = ++dim3LastInd;

        if(dim3Et.find(ball2) == dim3Et.end())
            dim3Et[ball2] = ++dim3LastInd;

        // add the new edge to the Adj list
        Adj[DIM3][ dim3Et[ball1] ].push_back(dim3Et[ball2]);
        Adj[DIM3][ dim3Et[ball2] ].push_back(dim3Et[ball1]);

        // do the same for the floor tree. Thus, ignoring z axe.
        get<2>(ball1) = 0;
        get<2>(ball2) = 0;

        if(dim2Et.find(ball1) == dim2Et.end())
            dim2Et[ball1] = ++dim2LastInd;

        if(dim2Et.find(ball2) == dim2Et.end())
            dim2Et[ball2] = ++dim2LastInd;

        Adj[DIM2][ dim2Et[ball1] ].push_back(dim2Et[ball2]);
        Adj[DIM2][ dim2Et[ball2] ].push_back(dim2Et[ball1]);

    }

    // for each WHITE node u with discovery time u.d :
    // run DFS and check if there is a back edge to a node v with discovery time v.d s.t u.d <= v.d - 2
    // -> there is a non trivial circle = closed chain
    for(int i = 1; i <= dim3LastInd; i++){
        if (closed[DIM3]) break;
        if(color[DIM3][i] == WHITE)
            DFS(DIM3, i, 0);
    }

    // do the same for the floor tree
    for(int i = 1; i <= dim2LastInd; i++){
        if (closed[DIM2]) break;
        if(color[DIM2][i] == WHITE)
            DFS(DIM2, i, 0);
    }

    cout << (closed[DIM3] ? "True closed chains" : "No true closed chains") << endl;
    cout << (closed[DIM2] ? "Floor closed chains" : "No floor closed chains") << endl;

    return 0;
}
