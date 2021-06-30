#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;
typedef pair<int, int> pii;

int main() {

	int n; cin >> n;
	vector<pii> v;

	for (int i = 0; i < n; i++) {
		int s, t; cin >> s >> t;
		v.push_back(make_pair(s, t));
	}
	sort(v.begin(), v.end());

	priority_queue<int, vector<int>, greater<int>> pq;

	int result = 0;
	for (int i = 0; i < n; i++) {
		while (!pq.empty() && v[i].first >= pq.top()) {
			pq.pop();
		}
		pq.push(v[i].second);

		int size = pq.size();
		result = max(result, size);
	}

	cout << result;

}