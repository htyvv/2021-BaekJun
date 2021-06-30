#include <iostream>

using namespace std;

int arr[10000];

struct Stack {
	
	int* ptr = arr;

	void push(int x) {
		*ptr = x;
		ptr++;
	}

	void pop() {
		if (arr == ptr) cout << -1 << "\n";
		else {
			cout << *(ptr-1) << "\n";
			ptr--;
		}
	}

	void size() {
		cout << ptr - arr << "\n";
	}

	void empty() {
		if (arr == ptr) cout << 1 << "\n";
		else cout << 0 << "\n";
	}

	void top() {
		if (arr == ptr) cout << -1 << "\n";
		else cout << *(ptr-1) << "\n";
	}
};

int main() {

	Stack stack;

	int n; cin >> n;

	while (n--) {
		string input; cin >> input;
		if (input == "push") {
			int x; cin >> x;
			stack.push(x);
		}
		else if (input == "pop") {
			stack.pop();
		}
		else if (input == "size") {
			stack.size();
		}
		else if (input == "empty") {
			stack.empty();
		}
		else if (input == "top") {
			stack.top();
		}
	}

}