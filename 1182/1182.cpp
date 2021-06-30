#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, s;
int input[21];
int cnt = 0;

void dfs(int idx, int sum) {

	sum += input[idx];

	if (idx == n) return;
	if (sum == s) cnt++;
	
	dfs(idx + 1, sum);
	dfs(idx + 1, sum - input[idx]);

}

int main() {
	
	cin >> n >> s;
	
	for (int i = 0; i < n; i++)	cin >> input[i];
	
	dfs(0, 0);

	cout << cnt;

}