#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main() {

	stack<double> s;

	int n; cin >> n;
	
	string input; cin >> input;

	vector<double> number(n);
	for (int i = 0; i < n; i++)	cin >> number[i];

	double result = 0.0f;
	int idx = 0;
	for (int i = 0; i < input.size(); i++) {
		if ('A' <= input[i] && input[i] <= 'Z') {
			s.push(number[input[i] - 'A']);
			idx++;
		}
		else {
			double second = s.top();
			s.pop();
			double first = s.top();
			s.pop();
			switch (input[i]) {
			case '+':
				s.push(first + second);
				break;
			case '-':
				s.push(first - second);
				break;
			case '*':
				s.push(first * second);
				break;
			case '/':
				s.push(first / second);
				break;
			}
		}
	}

	printf("%.2f", s.top());

}