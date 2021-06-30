#include <iostream>

using namespace std;

int dp[30][30];

int go(int n, int m) {

	if (dp[n][m]) return dp[n][m];
	if (n == m) return dp[n][m] = 1;
	if (n == 1) return dp[n][m] = m;
	if (m == 1) return dp[n][m] = n;

	int res = 0;
	for (int i = n - 1; i <= m - 1; i++) {
		res += go(n - 1, i);
	}
	dp[n][m] = res;
	return res;

}

int main() {

	int t, n, m; cin >> t;

	while (t--) {
		cin >> n >> m;
		cout << go(n, m) << "\n";
	}

}