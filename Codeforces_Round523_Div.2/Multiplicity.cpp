// Codeforces_Round523_(Div. 2)\C. Multiplicity
// Created by Gal Toubul

#include <bits/stdc++.h>
using namespace std;
typedef vector<int> VI;
typedef long long ll;
typedef vector<vector<ll>> VVI;
const ll M = 1000000007;

/** ------------------------------ solution explanation------------------------------------
 * I will explain about the following 3 solutions to the problem.
 * The first is failed due to memory limit.
 * The second is failed due to time limit.
 * The third is good according to the requirements.
 *
 *
 * ------------------------------------------- 1 --------------------------------------------------
 * These DP properties are the same for the second solution
 * dp[i][j] = # of subsequences using a1...ai with max length j
 * Therefore, the solution to the problem is sum of dp[n][j] for 1 <= j <= n
 * dp[i][0] = 1 for 1 <= i <= n since there is only the empty subsequence
 * dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1]  |   if a[i] is divisible by j
 * dp[i][j] = dp[i - 1][j - 1]                 |   if a[i] isn't divisible by j
 * Time complexity: O(n)
 * Space complexity: O(n^2) for dp mat
 *
 * Why the recursion formula is correct?
 * You can imagine we are trying to fill dp[i][j] for some i and j.
 * So, we are looking at the array [a1, a2, ..., ai] and trying to find the # of subsequences with max length j.
 * Therefore, if ai is divisible by j, then it is like taking all the good j-1 length prefixes
 * (let's say we have x of them) that are made from [a1, ..., ai-1] and attaching them ai,
 * and by that we will get x subsequences with max length j using [a1, a2, ..., ai].
 * In addition to that we can take all subsequences with max length j using [a1, a2, ..., ai-1] which are also
 * subsequences with max length j using [a1, a2, ..., ai].
 * If ai isn't divisible by j we will take only the subsequences with max length j using [a1, a2, ..., ai-1].
 *
 * This solution failed due to memory limit since O(n^2) = O(10^5 * 10^5 * 4B(per int)) > 256 * 10^6 = 256MB
 * */


int main(){
    ios::sync_with_stdio(0);

    ll n = 0;
    cin >> n;
    VI a (1e6+5);

//    VVI dp(n + 1, VI(n + 1, 0));
//    for (int i = 1; i <= n; ++i)
//        cin >> a[i];
//
//    for (int index = 0; index <= n; ++index)
//        dp[index][0] = 1;
//
//    for (int index = 1; index <= n; ++index) {
//        for (int length = 1; length <= n; ++length) {
//            if (a[index] % length == 0)
//                dp[index][length] = dp[index - 1][length] + dp[index - 1][length - 1];
//            else
//                dp[index][length] = dp[index - 1][length];
//        }
//    }
//
//    int sum = 0;
//    for (int length = 1; length <= n; length++)
//        sum += dp[n][length];

    VI dp(1e6+5, 0);
    dp[0] = 1;

/**
 * ------------------------------------------- 2 --------------------------------------------------
 * In order to get over the space limit we will notice we can make dp a 1D array instead of 2D.
 * We can do that by using a another loop for j axe.
 * By that, if we want, for example, to find dp[2][3],
 * then we will get to it when the inner loop reaches its 3rd iteration at the 2nd iteration of the outer loop
 *
 * We did saved space and got our desired O(n),
 * but we got time limit since our time complexity is now O(n^2) = O(10^5 * 10^5) > O(10^9) > O(10^8 + 0.5 * 10^8) = 3sec
*/

//    for (int index = 1; index <= n; ++index) {
//        for (int length = index; length > 0; length--) {
//            if (a[index] % length == 0)
//                dp[length] += dp[length - 1];
//        }
//    }
//
//    int sum = 0;
//    for (int i = 1; i <= n; i++)
//        sum += dp[i];

/**
 * ------------------------------------------- 3 --------------------------------------------------
 * And finally, the winner:
 * We will use the same space as at 2) and we will save time by:
 * calculating divisors for ai and then updating dp only for the new divisors
 *
 * How is it working?
 * You can imagine that at each point of the process we keep tracking on how many elements till now we have found
 * that are divisible by each number and when we explore the dividers of a new number and we will update dp by that:
 * dp[i] = dp[i] + dp[i-1] since there are dp[i-1] prefixes that we can attach with ai and get a i length subsequence
 * using [a1,..., ai]
 *
 *
 * For example, if at some point dp looks like that: [1, 3, 1, 0, ..., 0] (the array starts from a0).
 * Then, the program is looking for the dividers of 14, which are: 1, 14 , 2, and 7.
 * Let's look on updating dp[2] by dp[2] = dp[2] + dp[2-1] = 1 + 3 = 4
 * That is, now we have 4 2-size subsequence using [a1, a2], and it's true because we had 3 1-size prefixes that can
 * attach them with 14 and get 4 2-size subsequence using [a1, a2]
 *
 * Now, there is no space or time limit since:
 * time complexity = O(n * (sqrt(ai) * log (sqrt(ai)))) = O(10^5 * 10^3 * log(10^3)) < O(10^8 * 24) < O(10^8 + 0.5 * 10^8) = 3sec
 * space complexity = O(n)
 */
    for (int i = 1; i <= n; i++){ // O(n)
        cin >> a[i];

        // find divisors
        VI divisors;
        for (int j = 1; j * j <= a[i]; j++) { // O(sqrt(ai))
            if (a[i] % j == 0){
                divisors.push_back(j);
                if(j != a[i] / j)
                    divisors.push_back(a[i] / j);
            }
        }

        // we want to update dp from the end to start since the end of subsequence is depends on the prefix and not vice versa
        sort(divisors.begin(), divisors.end()); // O(sqrt(ai) * log (sqrt(ai)) )
        reverse(divisors.begin(), divisors.end());// O(sqrt(ai))

        // we will update dp only for the indices of ai divisors
        for (auto &it : divisors){ // O(sqrt(ai))
            dp[it] += dp[it - 1];
            dp[it] %= M;
        }
    }

    ll sum = 0;
    for (int i = 1; i <= n; i++)
        sum += dp[i];

    cout << sum % M ;

    return 0;
}
