#include <iostream>
#include <algorithm>

using namespace std;

int t[100000];

int main() {

	int n, k; cin >> n >> k;

	for (int i = 0; i < n; i++) {
		cin >> t[i];
	}

	int left = 0;
	int right = k-1;

	int sum = 0;
	for (int i = 0; i < k; i++) {
		sum += t[i];
	}

	int res = sum;
	while (1) {
		if (right == n-1) break;
		sum -= t[left++];
		sum += t[++right];
		res = max(res, sum);
	}

	cout << res;

}