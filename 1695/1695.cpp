#include <iostream>
#include <memory.h>

using namespace std;

int n;
int arr[5000];
int dp[5000][5000];

int palindrome(int left, int right) {
	if (left >= right) return 0;
	int ret = dp[left][right];
	if (ret != -1) return ret;
	ret = 0;
	if (arr[left] == arr[right]) ret += palindrome(left + 1, right - 1);
	else ret += 1 + min(palindrome(left, right - 1), palindrome(left + 1, right));
	return ret;
}

int main() {

	ios_base::sync_with_stdio(false); cout.tie(NULL); cin.tie(NULL);

	cin >> n;
	for (int i = 0; i < n; i++) cin >> arr[i];

	memset(dp, -1, sizeof(dp));
	cout << palindrome(0, n - 1);

	return 0;

}