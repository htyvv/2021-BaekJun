#include<iostream>
#include<queue>

using namespace std;

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL);

	priority_queue<int, vector<int>, greater<int>> pq;
	int n; cin >> n;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {

			int x; cin >> x;
			
			int size = pq.size();
			if (size < n) pq.push(x);
			else if (x > pq.top()) {
				pq.push(x);
				pq.pop();
			}
		}
	}

	cout << pq.top();
	
}