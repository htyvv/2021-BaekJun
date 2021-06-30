#include <iostream>
#include <queue>

typedef long long ll;
using namespace std;

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL);

	int t; cin >> t;

	while (t--) {

		priority_queue<ll, vector<ll>, greater<ll>> pq;

		int k; cin >> k;

		for (int i = 1; i <= k; i++) {
			ll input; cin >> input;
			pq.push(input);
		}

		ll total = 0;
		while (pq.size() != 1) {

			ll curr = pq.top();
			pq.pop();
			curr += pq.top();
			pq.pop();

			total += curr;

			pq.push(curr);

		}

		cout << total << "\n";

	}

}