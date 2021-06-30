#include<iostream>
#include<string>
#include<stack>

using namespace std;

int main() {

	stack<char> small_bracket;
	stack<char> big_bracket;
	string result = "yes";

	while (1) {
		string input; getline(cin, input);
		if (input == ".") break;

		for (int i = 0; i < input.size(); i++) {

			if (input[i] == '(') {
				small_bracket.push('(');
			}
			else if (input[i] == ')') {
				if (small_bracket.empty()) {
					result = "no";
					break;
				}
				else small_bracket.pop();
			}
			else if (input[i] == '[') {
				big_bracket.push('[');
			}
			else if (input[i] == ']') {
				if (big_bracket.empty()) {
					result = "no";
					break;
				}
				else big_bracket.pop();
			}
		}

		cout << result << "\n";

	}

}