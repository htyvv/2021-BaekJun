#include <iostream>
#include <algorithm>

using namespace std;

int main() {

	int n; cin >> n;
	int arr[1001];
	int dp[1001] = {0, };

	for (int i = 1; i <= n; i++) {
		cin >> arr[i];
	}

	dp[1] = 1;


	for (int i = 2; i <= n; i++) {
		for (int j = 1; j < i; j++) {
			if (arr[j] < arr[i]) {
				dp[i] = max(dp[i], dp[j]);
			}
		}
		dp[i]++;
	}

	cout << *max_element(dp, dp + n+1);

}