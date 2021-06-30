#include<iostream>
#include<algorithm>

using namespace std;

int dp[1001][3]; 
int price[1001][3];

int main(void) {

	int n;
	cin >> n;

	for (int i = 1; i <= n; i++)
		for (int j = 0; j < 3; j++)
			cin >> price[i][j];

	int result = 1000 * 1000 + 1;

	for (int k = 0; k <= 2; k++) {
		for (int i = 0; i <= 2; i++) {
			if (i == k) dp[1][i] = price[1][i];
			else dp[1][i] = 1000 * 1000 + 1;
		}
		for (int i = 2; i <= n; i++) {
			dp[i][0] = min(dp[i - 1][1], dp[i - 1][2]) + price[i][0];
			dp[i][1] = min(dp[i - 1][0], dp[i - 1][2]) + price[i][1];
			dp[i][2] = min(dp[i - 1][0], dp[i - 1][1]) + price[i][2];
		}
		for (int i = 0; i <= 2; i++) {
			if (i == k) continue;
			result = min(result, dp[n][i]);
		}
	}

	cout << result << '\n';
}