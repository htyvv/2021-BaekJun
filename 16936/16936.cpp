#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;
typedef long long ll;

ll n;
vector<ll> v;
vector<ll> r;

void DFS(ll curr, int depth) {
	if (depth == n) {
		for (auto it : r) cout << it << " ";
		return;
	}
	if (binary_search(v.begin(), v.end(), curr * 2)) {
		r.push_back(curr * 2);
		DFS(curr * 2, depth + 1);
		r.pop_back();
	}
	if (curr % 3 == 0 && binary_search(v.begin(), v.end(), curr / 3)) {
		r.push_back(curr / 3);
		DFS(curr / 3, depth + 1);
		r.pop_back();
	}
	return;
}

int main() {

	cin >> n;
	for (int i = 0; i < n; i++) {
		ll input; cin >> input; v.push_back(input);
	}
	sort(v.begin(), v.end());

	for (auto curr : v) {
		r.push_back(curr);
		DFS(curr, 1);
		r.pop_back();
	}


	return 0;
} 