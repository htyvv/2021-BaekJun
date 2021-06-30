#include <iostream>

using namespace std;

int arr[10001];

int main() {

	int cnt = 0;
	int n, m; cin >> n >> m;
	
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	int l = 0, r = 0, sum = arr[0];

	while (1) {
		if (sum == m) cnt++;
		
		if (sum <= m) sum += arr[++r];
		else sum -= arr[l++];	

		if (r == n) break;
	}

	cout << cnt;

}