// Educational Codeforces Round 82/A. Erasing Zeroes
// Created by Gal Toubul

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <set>
#include <map>
#include <queue>
using namespace std;
typedef long long ll;
typedef vector<int> VI;
typedef vector<ll> VL;
typedef vector<vector<int>> VVI;

int main(){
    ios::sync_with_stdio(0);
    int T;
    cin >> T;
    for(int t = 1; t <= T; t++)
    {
        string s;
        cin >> s;

        int i = 0;
        while (s.at(i) != 1)
            i++;

        int j = s.length() - 1;
        while (s.at(j) != 1)
            j--;

        int counter = 0;
        while (i != j){
            if(s.at(i) == 0)
                counter++;
            i++;
        }

        cout << counter << endl;
    }
    return 0;
}

