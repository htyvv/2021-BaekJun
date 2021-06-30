#include<iostream>
#include<deque>
#include<string>

using namespace std;

int main() {

	int t; cin >> t;

	while (t--) {

		string p; cin >> p;

		int n; cin >> n;

		deque<int> dq;
		bool isReverse = false;
		bool isError = false;

		string input; cin >> input;
		string temp = "";

		for (int i = 1; i < input.size(); i++) {
			if (input[i] == ',' || input[i] == ']') {
				if (temp == "") break;
				int t = stoi(temp);
				dq.push_back(t);
				temp = "";
			}
			else temp += input[i];
		}

		for (int i = 0; i < p.size(); i++) {
			switch (p[i]) {
			case 'R':
				if (isReverse) isReverse = false;
				else isReverse = true;
				break;
			case 'D':

				if (dq.empty()) {
					isError = true;
					break;
				} 

				if (isReverse) dq.pop_back();		
				else dq.pop_front();				
				break;
			}
		}
		
		int size = (int)dq.size();

		if (isError) {
			cout << "error\n";
		}
		else if (isReverse) {
			cout << "[";
			for (int i = size - 1; i >= 0; i--) {
				cout << dq[i];
				if(i != 0) cout << ",";
			}
			cout << "]\n";
		}
		else {
			cout << "[";
			for (int i = 0; i <= size - 1; i++) {
				cout << dq[i];
				if (i != size - 1) cout << ",";
			}
			cout << "]\n";

		}
	}

}