#include <iostream>

using namespace std;

int n;
int arr[8];
int tmp[8];
bool is_used[8];
int max_result;


void calculate_abs() {
	int cur_result = 0;
	for (int i = 0; i < n-1; i++) {
		cur_result += abs(tmp[i] - tmp[i + 1]);
	}
	max_result = max(max_result, cur_result);
}

void dfs(int cnt) {

	if (cnt == n) {
		calculate_abs();
		return;
	}

	for (int i = 0; i < n; i++) {
		if (!is_used[i]) {
			is_used[i] = true;
			tmp[cnt] = arr[i];
			dfs(cnt + 1);
			is_used[i] = false;
		}
	}

}

int main() {
	
	cin >> n;
	for (int i = 0; i < n; i++) cin >> arr[i];
	dfs(0);
	cout << max_result;

}