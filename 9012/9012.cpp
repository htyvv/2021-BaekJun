#include <iostream>

using namespace std;

int main() {

	int t; cin >> t;
	
	while (t--) {

		string input; cin >> input;

		bool isFail = false;
		int left_bracket = 0;
		for (int i = 0; i < input.size(); i++) {
			if (input[i] == '(') {
				left_bracket++;
			}
			else if (left_bracket != 0) {
				left_bracket--;
			}
			else {			
				isFail = true;
				break;
			}
		}
		if (isFail) cout << "NO" << "\n";
		else if (left_bracket) cout << "NO" << "\n";
		else cout << "YES" << "\n";
	}
	
}