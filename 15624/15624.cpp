#include <iostream>
#include <vector>

using namespace std;

vector<long long> dp;

void fib(int num) {
	for (int i = 2; i <= num; i++) {
		dp.push_back((dp[i - 1] + dp[i - 2]) % 1000000007);
	}
}

int main() {

	int n; cin >> n;

	if (n == 0) cout << 0;
	else if (n == 1) cout << 1;
	else {
		dp.push_back(0);
		dp.push_back(1);
		fib(n);

		cout << dp.back();
	}
	
}