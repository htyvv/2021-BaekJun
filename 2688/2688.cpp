#include <iostream>
#include <cstring>

using namespace std;

int main() {

	int t; cin >> t;

	while (t--) {
		int n; cin >> n;
		long long dp[65][10];
		memset(dp, 0, sizeof(dp));

		for (int i = 1; i <= n; i++) {
			for (int j = 0; j <= 9; j++) {
				if (i == 1) {
					dp[i][j] = 1;
					continue;
				}
				for (int idx = 0; idx <= 9; idx++) {
					if (idx >= j) {
						dp[i][j] += dp[i - 1][idx];
					}
				}
			}
		}

		long long result = 0;
		for (int k = 0; k <= 9; k++) {
			result += dp[n][k];
		}

		cout << result << "\n";

	}

}