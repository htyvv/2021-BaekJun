#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {

	string input; cin >> input;
	vector<char> name(input.begin(), input.end());

	bool isAlone = false;
	char alone = ' ';

	string result = "";
	int i = 0;

	while(1) {

		if (i == name.size()) break;
		if (name[i] == ' ') {
			i++;
			continue;
		} 

		auto it = find(name.begin() + i + 1, name.end(), name[i]);

		if (it != name.end()) {
			result += name[i];
			*it = ' ';
		}
		else if (isAlone == false) {
			isAlone = true;
			alone = name[i];
		}
		else{
			cout << "I'm Sorry Hansoo";
			return 0;
		}

		i++;
	}

	cout << result << alone;
	for (int i = result.size() - 1; i >= 0; i--) cout << result[i];

}