#include <iostream>
#include <string>
using namespace std;

int main() {

	int n, m;
	int ans;
	int len;
	char input[50][50];

	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> input[i][j];
		}
	}

	len = min(n, m) - 1;

	for (int k = 0; k <= len; k++) {
		bool check = false;
		for (int i = 0; i < n - k; i++) {
			for (int j = 0; j < m - k; j++) {
				if (input[i][j] == input[i][j + k] && input[i][j] == input[i + k][j] && input[i][j] == input[i + k][j + k]) {
					ans = k + 1;
					check = true;
					break;
				}
				if (check) {
					break;
				}
			}
		}


	}
	cout << ans * ans;


}
