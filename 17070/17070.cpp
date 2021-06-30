#include <iostream>

using namespace std;

int h[17][17];
int dp[17][17][3];

int main() {

	int n; cin >> n;
	

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> h[i][j];
		}
	}

	dp[1][2][0] = 1;

	for (int r = 1; r <= n; r++) {
		for (int c = 1; c <= n; c++) {

			if (r == 1 && c <= 2) continue;
			if (h[r][c] == 1) continue;

			for (int idx = 0; idx <= 2; idx++) {
				if (idx == 0) {
					dp[r][c][idx] = dp[r][c - 1][0] + dp[r][c - 1][2];
				}
				else if (idx == 1) {
					dp[r][c][idx] = dp[r - 1][c][1] + dp[r - 1][c][2];
				}
				else {
					if (h[r - 1][c] == 0 && h[r][c - 1] == 0)
						dp[r][c][idx] = dp[r - 1][c - 1][0] + dp[r - 1][c - 1][1] + dp[r - 1][c - 1][2];
					else continue;
				}
			}
		}
	}

	cout << dp[n][n][0] + dp[n][n][1] + dp[n][n][2];

}