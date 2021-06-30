#include <iostream>
#include <map>

using namespace std;

int main() {

	ios_base::sync_with_stdio(0); cin.tie(0);

	int t; cin >> t;
	while (t--) {

		int n; cin >> n;
		map<string, int> cloth;

		while (n--) {
			string dummy, input; cin >> dummy >> input;
			cloth[input] += 1;
		}

		int res = 1;
		for(auto num : cloth) {
			res *= (num.second + 1);
		}
		res--;

		cout << res << "\n";

	}

}