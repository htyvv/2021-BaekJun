#include <iostream>
#include <algorithm>
#include <vector>

typedef long long ll;
using namespace std;

int m, n;
vector<ll> snack;

bool check(ll mid) {
	ll cnt = 0;
	int start_idx = lower_bound(snack.begin(), snack.end(), mid) - snack.begin();
	for (int i = start_idx; i < snack.size(); i++) {
		cnt += (snack[i] / mid);
	}
	if (cnt >= m) {
		return true;
	}
	else return false;
}

int main() {

	cin >> m >> n;
	snack.resize(n);
	for (int i = 0; i < n; i++) cin >> snack[i];

	ll left = 1;
	ll right = *max_element(snack.begin(), snack.end());
	ll mid = 0;
	ll ans = 0;

	while (left <= right) {
		mid = (left + right) / 2;
		if (check(mid)) {
			ans = mid;
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}

	cout << ans;

}