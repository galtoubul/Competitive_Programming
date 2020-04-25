// Educational Codeforces Round 81/B. Infinite Prefixes
// Created by Gal Toubul

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(){
    ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while(t--)
    {
        int n, x;
        string s;
        cin >> n >> x >> s;

        int count0 = 0, count1 = 0, countPrefix = 0;
        vector<int> bal(n);
        for (int i = 0; i < n; i++){
            if (s.at(i) == '0')
                count0++;
            else
                count1++;
            bal[i] = count0 - count1;
        }

        int delta = bal[n - 1];

        // if x = 0 -> there is already 1 prefix: the empty string
        if (x == 0)
            countPrefix++;

        // for each i: there is a prefix of t s.t balance = x iff exists a k s.t bal[i] + delta * k = x
        // -> iff (x - bal[i]) % delta == 0 && k >= 0
        int balance = x + 1; // only for balance != x
        count0 = count1 = 0;
        for (int i = 0; i < n; i++){

            //if at some point delta == 0 && balance == x then we will be able to repeat this prefix infinite times
            if(delta == 0){
                if (balance == x){
                    countPrefix = -1;
                    break;
                }
            }

            else if((x - bal[i]) / delta >= 0 && (x - bal[i]) % delta == 0){
                countPrefix++;
            }

            if (s.at(i) == '0')
                count0++;
            else
                count1++;
            balance = count0 - count1;
        }

        delta == 0 && balance == x ? countPrefix = -1 : countPrefix = countPrefix;
        cout << countPrefix << endl;
    }
    return 0;
}
