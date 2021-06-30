#include <iostream>

using namespace std;

int main() {

	int t; cin >> t;

	long long p[7] = { 0,1,1,1,2,2,3 };

	while (t--) {

		int n; cin >> n;
		long long dp[101] = {0, };

		for (int i = 1; i <= n; i++) {
			if (i <= 6) {
				dp[i] = p[i];
			}
			else {
				dp[i] = dp[i - 1] + dp[i - 5];
			}
		}

		cout << dp[n] << "\n";

	}

}