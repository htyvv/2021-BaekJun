#include <iostream>

using namespace std;

int main() {
	int n; cin >> n;
	
	if (n == 1 || n == 3) {
		cout << -1;
		return 0;
	}

	int five, two;
	five = n / 5;

	if ((n%5)%2 == 0) {
		n %= 5;
	}
	else {
		five--;
		n = n - 5 * five;
	}
	two = n / 2;
	n %= 2;
	
	if (n) {
		cout << -1;
	}
	else cout << five + two;

}