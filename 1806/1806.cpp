#include <iostream>
#include <climits>
#include <algorithm>

using namespace std;

int arr[100000];

int main() {

	int n, s; cin >> n >> s;

	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	int left = 0;
	int right = 0;
	int sum = arr[left];
	int min_length = INT_MAX;

	while (1) {

		if (right == n) break;

		if (sum >= s) {
			min_length = min(min_length, right - left + 1);
			sum -= arr[left++];
		}
		else {
			sum += arr[++right];
		}

	}

	if (min_length == INT_MAX) {
		cout << 0;
	}
	else cout << min_length;
}