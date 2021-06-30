#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int n, k;
vector<int> liq;

bool check(int mid) {
	int cnt = 0;
	for (auto it : liq) {
		cnt += (it / mid);
	}
	if (cnt >= k) {
		return true;
	}
	else return false;
}

int main() {

	cin >> n >> k;
	liq.resize(n);
	for (int i = 0; i < n; i++) cin >> liq[i];

	int left = 1;
	int right = *max_element(liq.begin(), liq.end());
	int mid = 0;
	int ans = 0;
	while (left <= right) {
		mid = (left + right) / 2;
		if (check(mid)) {
			left = mid + 1;
			ans = mid;
		}
		else {
			right = mid - 1;
		}
	}

	cout << ans;

}