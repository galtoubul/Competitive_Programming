// Codeforces Round #648 (Div. 2) \ A. Matrix Game
// Created by Gal Toubul
#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--){
        int n, m;
        cin >> n >> m;
        vector<bool> cols(m, false);
        vector<bool> rows(n, false);
        vector<vector<int>> mat(n, vector<int>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> mat[i][j];
                if(mat[i][j] == 1){
                    if(cols[j] == false)
                        cols[j] = true;
                    if(rows[i] == false)
                        rows[i] = true;
                }
            }
        }

        int colsInd = 0, rowsInd = 0, counter = 0;
        while(colsInd < m && rowsInd < n){
            while(colsInd < m && cols[colsInd])
                colsInd++;
            while(rowsInd < n && rows[rowsInd])
                rowsInd++;
            if(colsInd == m || rowsInd == n) break;

            if(!cols[colsInd] && !rows[rowsInd])
                counter++;

            colsInd++; rowsInd++;
        }

        if(counter % 2 == 1)
            cout << "Ashish" << endl;
        else
            cout << "Vivek" << endl;
    }
    return 0;
}
