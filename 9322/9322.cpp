#include<iostream>
#include<map>
#include<vector>

using namespace std;

int main() {

	int t; cin >> t;

	while (t--) {

		ios::sync_with_stdio(false); cin.tie(NULL);

		int n; cin >> n;

		map<string, int> key1;

		for (int i = 0; i < n; i++) {
			string input; cin >> input;
			key1[input] = i;
		}

		vector<int> serial_idx;
		for (int i = 0; i < n; i++) {
			string input; cin >> input;
			serial_idx.push_back(key1.find(input)->second);
		}

		map<int, string> normal;
		for (int i = 0; i < n; i++) {
			string input; cin >> input;
			normal[serial_idx[i]] = input;
		}

		for (int i = 0; i < n; i++) {
			cout << normal[i] << " ";
		}
		cout << "\n";

	}

}