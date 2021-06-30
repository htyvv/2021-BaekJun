#include <iostream>
#include <string>
#include <map>

using namespace std;

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int n, m; cin >> n >> m;
	map<string, int> pokemon1;
	map<int, string> pokemon2;

	string name_input;
	for (int i = 1; i <= n; i++) {
		cin >> name_input;
		pokemon1[name_input] = i;
		pokemon2[i] = name_input;
	}

	string question_input;
	while (m--) {
		cin >> question_input;
		if ('A' <= question_input[0] && question_input[0] <='Z') {
			cout << pokemon1[question_input] << "\n";
		}
		else {
			cout << pokemon2[stoi(question_input)] << "\n";
		}
	}

}