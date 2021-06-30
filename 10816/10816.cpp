#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

	int n; cin >> n;
	vector<int> card(n);
	for (int i = 0; i < n; i++) cin >> card[i];
	sort(card.begin(), card.end());

	int m; cin >> m;
	vector<int> check(m);
	for (int i = 0; i < m; i++) cin >> check[i];

	for (auto it : check) {
		cout << upper_bound(card.begin(), card.end(), it) - lower_bound(card.begin(), card.end(), it) << " ";
	}

}