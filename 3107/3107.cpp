#include<iostream>
#include<deque>
#include<string>
#include<sstream>

using namespace std;

string input;
deque<string> ip;

int main() {
	
	cin >> input;
	stringstream ss(input);

	int cnt = 0;
	string temp;
	while (getline(ss, temp, ':')) {
		while (temp.size() != 4) {
			temp = "0" + temp;
		}
		ip.push_back(temp);
		cnt++;
	}

	if (ip.size() != 8) {
		deque<string>::iterator it = ip.begin();
		for (; it != ip.end(); it++) {
			if (*it == "0000") {
				for (int i = 0; i < 8 - cnt; i++) {
					it = ip.insert(it, "0000");
				}
				break;
			}
		}
	}

	if (ip.size() == 9) ip.pop_front();

	for (int i = 0; i < ip.size(); i++) {
		cout << ip[i];
		if (i != ip.size() - 1) cout << ":";
	} 

	return 0;
}