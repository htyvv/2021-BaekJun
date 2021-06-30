#include<iostream>
#include<queue>
#include<vector>

using namespace std;

int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n; cin >> n;
	queue<int> b;
	vector<int> p;

	for (int i = 1; i <= n; i++) {
		b.push(i);
	}

	for (int i = 0; i < n; i++) {
		int input; cin >> input;
		p.push_back(input);
	}

	for(int i = 0; i < n; i++) {

		int curr = p[b.front() - 1];
		cout << b.front() << " ";
		b.pop();
		if (!b.empty()) {
			if (curr > 0) {
				for (int i = 1; i <= curr - 1; i++) {
					b.push(b.front());
					b.pop();
				}
			}
			else {
				for (int i = 1; i <= b.size() + curr; i++) {
					b.push(b.front());
					b.pop();
				}
			}
		}	
	}

}