#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    ios::sync_with_stdio(0);
    ll t, N, B, M;
    cin >> t;
    while (t--){
        cin >> N >> B >> M;
        ll counter = 0, lastBlock = -1, a;
        for (int i = 0; i < M; ++i) {
            cin >> a;
            if((a / B) != lastBlock){
                counter++;
                lastBlock = a / B;
            }
        }
        cout << counter << endl;
    }
    return 0;
}
