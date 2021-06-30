#include <iostream>
#include <numeric>
#include <stack>

using namespace std;

int main() {

	int k; cin >> k;
	stack<int> s;

	int input;
	while (k--) {
		cin >> input;
		if (input != 0) {
			s.push(input);
		}
		else s.pop();
	}

	int sum = 0;
	while(!s.empty()) {
		sum += s.top();
		s.pop();
	}
	
	cout << sum;

}