#include<iostream>
#include<string>
#include<vector>
#include<set>

using namespace std;

int n, k;
string deck[10];
bool check[10];
set<string> result;
vector<string> tmp;

string change() {
	string str = "";
	for (auto a : tmp) {
		str += a;
	}
	return str;
}

void dfs(int cnt) {

	if (cnt == k) {
		result.insert(change());
		return;
	}

	for (int i = 0; i < n; i++) {
		if (check[i] == false) {
			check[i] = true;
			tmp.push_back(deck[i]);
			dfs(cnt + 1);
			tmp.pop_back();
			check[i] = false;
		}
		
	}
}

int main() {

	cin >> n >> k;

	for (int i = 0; i < n; i++) {
		cin >> deck[i];
	}
	
	dfs(0);

	cout << result.size();

}