#include <iostream>

using namespace std;

int dp[201][201];

int main() {

	const int m = 1000000000;

	int N, K; cin >> N >> K;

	for (int k = 1; k <= K; k++) {
		for (int n = 0; n <= N; n++) {
			if (n == 0 || k == 1) {
				dp[n][k] = 1;
				continue;
			}
			dp[n][k] = (dp[n][k - 1] + dp[n - 1][k]) % m;
		}
	}

	cout << dp[N][K];

}