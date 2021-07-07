#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<char> a;
vector<bool> isVisited;
vector<char> r;
int b;
int n;
int max_result = -1;

void DFS(int depth) {
	if (depth == n) {
		if (r[0] == '0') return;
		string temp = "";
		for (auto i : r) temp += i;
		int curr_result = stoi(temp);
		if (curr_result <= b) max_result = max(max_result, curr_result);
		return;
	}
	for (int i = 0; i < n; i++) {
		if (isVisited[i] == false) {
			r.push_back(a[i]);
			isVisited[i] = true;
			DFS(depth + 1);
			r.pop_back();
			isVisited[i] = false;
		}
	}
}

int main() {

	string A; string B; cin >> A >> B;
	for (auto t : A) a.push_back(t);
	b = stoi(B);
	n = a.size();
	for (int i = 0; i < n; i++) isVisited.push_back(false);

	DFS(0);
	cout << max_result;

	return 0;
}