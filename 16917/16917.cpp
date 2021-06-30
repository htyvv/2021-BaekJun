#include<iostream>

using namespace std;

int main() {

	int a, b, c, x, y;
	cin >> a >> b >> c >> x >> y;

	int result = 0;
	if (a + b > c * 2) {
		result += c * 2 * min(x, y);
		if (a > c * 2) {
			result += (x - min(x, y)) * c * 2;
		}
		else {
			result += (x - min(x, y)) * a;
		}
		if (b > c * 2) {
			result += (y - min(x, y)) * c * 2;
		}
		else {
			result += (y - min(x, y)) * b;
		}	
	}
	else {
		result += x * a;
		result += y * b;
	}

	cout << result;

	return 0;
}