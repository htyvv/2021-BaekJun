#include <iostream>

using namespace std;

int main() {

	int cnt = 0;
	int n; cin >> n;

	for (int i = 1; i <= n; i++) {
		int sum = 0;
		int j = i;
		while (sum < n) {
			sum += j;
			j++;
		}
		if (sum == n) cnt++;
	}

	cout << cnt;

}