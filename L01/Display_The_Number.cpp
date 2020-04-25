// CodeForces/Educational Codeforces Round 81/A. Display The Number
// Created by Gal Toubul

#include <iostream>
#include <string>
using namespace std;
typedef long long ll;

int main(){
    ios::sync_with_stdio(0);
    int t;
    cin >> t;

    while (t--){
        int n;
        cin >> n;
        // the best way to get a bigger number is by adding 7 or 1 to the MSB, because they require only 2 or 3 segments
        // and if we an odd number than it's better to place 7 at the MSB and not at the LSB
        // printing strings instead of working with long long is mandatory since the program should with n<=10^5
        if (n % 2 == 1) {
            cout << "7";
            n -= 3;
        }
        while (n >= 2) {
            cout << "1";
            n -= 2;
        }
        cout << endl;
    }
    return 0;
}
