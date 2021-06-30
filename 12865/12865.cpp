#include <iostream>

using namespace std;

// dp[i][j] = i��° stuffs ���� ��������� ���԰� j�ΰ�� �ִ� ��ġ��
int dp[101][100001];

int main() {

	int n, k; cin >> n >> k;

	pair<int, int> stuffs[101];
	int result = 0;

	// first = ���� , second = ��ġ
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