#include <iostream>
#include <algorithm>

using namespace std;

int dp[1001][1001];

int main() {

	string st1, st2; cin >> st1 >> st2;

	for (int i = 1; i <= st2.size(); i++) {

		for (int j = 1; j <= st1.size(); j++) {

			if (st2[i - 1] == st1[j - 1])
				dp[i][j] = dp[i - 1][j - 1] + 1;
			else
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);

		}

	}

	cout << dp[st2.size()][st1.size()];

}