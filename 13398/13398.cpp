#include<iostream>
#include<algorithm>

using namespace std;

int arr[100001];
int dp[100001][2];

int main() {

    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int result = arr[0];

    for (int i = 0; i < n; i++) {

        dp[i][0] = dp[i][1] = arr[i];

        if (i == 0) continue;

        dp[i][0] = max(dp[i - 1][0] + arr[i], arr[i]);
        dp[i][1] = max(dp[i - 1][0], dp[i - 1][1] + arr[i]);

        result = max(result, max(dp[i][0], dp[i][1]));

    }
    cout << result << '\n';

    return 0;
}