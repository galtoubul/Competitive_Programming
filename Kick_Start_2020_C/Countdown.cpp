// Kick_Start_2020_C / A. Countdown
// Created by Gal Toubul
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(){
    ios::sync_with_stdio(0);
    int T;
    cin >> T;
    for (int i = 1; i < T + 1; ++i) {
        int ans = 0, N, K;
        cin >> N >> K;
        vector <int> vec (N);
        for (int j = 0; j < N; ++j)
            cin >> vec[j];

        int ptr = 0;
        while(ptr < vec.size()){

            // finding next start of a possible K-countdown
            while (ptr < vec.size() && vec[ptr] != K)
                ptr++;

            // it can't be a K-countdown if there aren't K places till the end of the array
            if(ptr + K <= vec.size()){
                int k = 1;

                // check if the next K - 1 places is a decreasing arithmetic sequence with the difference of 1
                for (; k < K; ++k) {
                    int next = ptr + 1;
                    if(vec[ptr] - 1 == vec[next])
                        ptr++;
                    else
                        break;
                }

                // it's a K-countdown
                if (vec[ptr] == 1 && k == K)
                    ans++;
            }
            ptr++;
        }
        cout << "Case #" << i << ": " << ans << endl;
    }
    return 0;
}