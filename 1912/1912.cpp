#include <iostream>

using namespace std;

int arr[100001];
int dp[100001];

int main() {

	int n; cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> arr[i];
	}
	
	dp[1] = arr[1];
	int ans = dp[1];

	for (int i = 2; i <= n; i++) {	
		dp[i] = max(dp[i - 1] + arr[i], arr[i]);
		ans = max(dp[i], ans);
	}

	cout << ans;

}