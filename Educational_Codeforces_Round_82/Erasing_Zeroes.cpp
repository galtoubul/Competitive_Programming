// Educational Codeforces Round 82/A. Erasing Zeroes
// Created by Gal Toubul

#include <iostream>
#include <string>
using namespace std;

int main(){
    ios::sync_with_stdio(0);
    int T;
    cin >> T;
    for(int t = 1; t <= T; t++)
    {
        string s;
        cin >> s;

        // finding first occurrence of 1 from left
        int i = 0;
        while (i < s.length() && s.at(i) != '1')
            i++;

        // finding first occurrence of 1 from right
        int j = s.length() - 1;
        while (j < s.length() && s.at(j) != '1')
            j--;

        // counting all zeros between the most left 1 to the most right 1
        int counter = 0;
        while (i < j){
            if(s.at(i) == '0')
                counter++;
            i++;
        }

        cout << counter << endl;
    }
    return 0;
}
