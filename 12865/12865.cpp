#include <iostream>

using namespace std;

// dp[i][j] = i번째 stuffs 까지 고려했을때 무게가 j인경우 최대 가치값
int dp[101][100001];

int main() {

	int n, k; cin >> n >> k;

	pair<int, int> stuffs[101];
	int result = 0;

	// first = 무게 , second = 가치
	for (int i = 1; i <= n; i++) {
		cin >> stuffs[i].first >> stuffs[i].second;
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= k; j++) {
			if (j >= stuffs[i].first) {
				dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - stuffs[i].first] + stuffs[i].second);
			}
			else dp[i][j] = dp[i - 1][j];
			result = max(result, dp[i][j]);
		}
	}

	cout << result;

}