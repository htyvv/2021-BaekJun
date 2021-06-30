#include<iostream>
#include<queue>

using namespace std;

struct compare {
	bool operator()(const int& a, const int& b) {
		if (abs(a) == abs(b)) {
			return a > b;
		}
		else {
			return abs(a) > abs(b);
		}
	}
};

int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	priority_queue<int, vector<int>, compare> pq;

	int command; cin >> command;

	while (command--) {

		int input; cin >> input;

		if (input == 0) {
			if (pq.empty()) cout << 0 << "\n";
			else {
				cout << pq.top() << "\n";
				pq.pop();
			}
		}
		else {
			pq.push(input);
		}

	}

}