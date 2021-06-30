#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool cmp(const pair<int, pair<int, bool>>& a, const pair<int, pair<int, bool>>& b) {
	if (a.second.first == b.second.first) return a.first < b.first;
	else return a.second.first > b.second.first;
}

int main() {

	int t; cin >> t;
	while (t--) {

		// map 순서, 중요도, 찾고자하는 번호
		vector<pair<int, pair<int, bool>>> printer;
		int n, m; cin >> n >> m;
		for (int i = 0; i < n; i++) {
			int input; cin >> input;
			if (i == m) {
				printer.push_back(pair<int, pair<int, bool>>(i, pair<int, bool>(input, true)));
			}
			else printer.push_back(pair<int, pair<int, bool>>(i, pair<int, bool>(input, false)));

		}

		sort(printer.begin(), printer.end(), cmp);

		for (int i = 0; i < n; i++) {
			if (printer[i].second.second == true) {
				cout << i + 1 << "\n";
				break;
			}
		}

	}

}