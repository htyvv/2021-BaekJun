#include <iostream>
#include <vector>
#include <stack>

using namespace std;

stack<int> s;
vector<int> a;

int main() {

	int n; cin >> n;
	a.resize(n);

	for (int i = 0; i < n; i++) cin >> a[i];


	int curr = 1;
	int idx = 0;
	string result = "";
	while (curr != n+1) {
		s.push(curr);
		result += "+\n";
		while (idx < n && a[idx] == s.top()) {
			s.pop();
			result += "-\n";
			idx++;
			if (s.empty()) break;
		}
		curr++;
	}

	if (s.empty()) cout << result;
	else cout << "NO";

}