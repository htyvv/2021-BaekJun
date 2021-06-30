#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;
typedef pair<int, int> p;

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL);

	priority_queue <pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	vector<p> room;

	int n; cin >> n;
	for (int i = 0; i < n; i++) {
		int idx, s, e; cin >> idx >> s >> e;
		room.push_back(p(s, e));
	}
	sort(room.begin(), room.end());

	int cnt = 0;

	for (int i = 0; i < n; i++ ) {

		while (!pq.empty() && room[i].first >= pq.top().first) {
			pq.pop();
		}
	
		pq.push(p(room[i].second, room[i].first));

		int size = pq.size();
		cnt = max(cnt, size);
	}


	cout << cnt;

}