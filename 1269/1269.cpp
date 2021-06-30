#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <set>

using namespace std;

int main() {

	string dummy;
	getline(cin, dummy, '\n');

	set<int> a;
	set<int> b;

	string element;

	string a_input;
	getline(cin, a_input, '\n');
	stringstream sa(a_input);
	while (getline(sa, element, ' ')) {
		a.insert(stoi(element));
	}

	string b_input;
	getline(cin, b_input, '\n');
	stringstream sb(b_input);
	while (getline(sb, element, ' ')) {
		b.insert(stoi(element));
	}
	
	int cnt = 0;
	for (auto i : a) {
		if (b.find(i) != b.end()) {
			cnt++;
		}
	}

	cout << a.size() + b.size() - 2 * cnt;

}