#include <iostream>

using namespace std;

int score[301];
int dp[301][2];

int main() {
	int stair; cin >> stair;
	for (int i = 1; i <= stair; i++) {
		cin >> score[i];
	}

	dp[0][0] = 0;
	dp[0][1] = 0;
	dp[1][0] = score[1];
	dp[1][1] = score[1];

	for (int i = 2; i <= stair; i++) {
		dp[i][0] = max(dp[i - 2][0], dp[i - 2][1]) + score[i];
		dp[i][1] = dp[i-1][0] + score[i];
	}
	
	cout << max(dp[stair][0], dp[stair][1]);


}