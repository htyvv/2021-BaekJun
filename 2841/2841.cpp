#include<iostream>
#include<vector>
#include<stack>

using namespace std;

int main() {

	int n, p; cin >> n >> p;
	vector<stack<int>> guitar(7);

	int cnt = 0;
	while (n--) {
	
		int line, fret; cin >> line >> fret;

		

		if (!guitar[line].empty() && guitar[line].top() > fret) {
			while (!guitar[line].empty() && guitar[line].top() > fret) {
				guitar[line].pop();
				cnt++;
			}
			if (!guitar[line].empty() && guitar[line].top() == fret) {
				continue;
			}	
			else {
				guitar[line].push(fret);
				cnt++;
			}
		}

		else if (!guitar[line].empty() && guitar[line].top() == fret) {
			continue;
		}

		else {
			guitar[line].push(fret);
			cnt++;
		}

	}

	cout << cnt;

}