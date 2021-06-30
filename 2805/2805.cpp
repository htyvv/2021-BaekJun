#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

vector<ll> trees;
ll n, m;

bool check(ll height) {
	ll rest = 0;
	for (auto it : trees) {
		if(it > height) rest += it - height;
	}
	if (rest >= m)
		return true;
	else
		return false;
}

int main() {
	
	cin >> n >> m;
	trees.resize(n);

	ll tmp;
	for (int i = 0; i < n; i++) {
		cin >> tmp;
		trees.push_back(tmp);
	}
	sort(trees.begin(), trees.end());

	ll left = 1;
	ll right = trees.back();
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