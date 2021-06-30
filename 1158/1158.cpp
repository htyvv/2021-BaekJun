#include<iostream>
#include<queue>

using namespace std;

int main() {

	int n, k; cin >> n >> k;
	queue<int> q;
	cout << "<";

	for (int i = 1; i <= n; i++) q.push(i);

	while (1) {
		for (int i = 0; i < k-1; i++) {
			q.push(q.front());
			q.pop();
		}
		cout << q.front();
		q.pop();
		if (q.empty()) break;
		cout << ", ";
	}
	cout << ">";

}