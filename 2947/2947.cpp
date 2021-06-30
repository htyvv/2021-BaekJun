#include <iostream>
#include <algorithm>

using namespace std;

int main() {

	int check[5] = {1,2,3,4,5};
	int input[5];
	for (int i = 0; i < 5; i++) cin >> input[i];
	
	while (!equal(input, input+5, check)) {
		for (int i = 0; i < 4; i++) {
			if (input[i] > input[i + 1]) {
				swap(input[i], input[i + 1]);
				for (int i = 0; i < 5; i++) {
					cout << input[i] << " ";
				}
				cout << "\n";
			}
		}
	}
}