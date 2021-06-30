#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

bool p[40000001];
vector<int> prime;

int main() {

	int n; cin >> n;

	memset(p, true, sizeof(p));


	for (int i = 2; i <= n; i++) {
		for (int j = 2; i * j <= n; j++) {
			p[i * j] = false;
		}
	}


	for (int i = 2; i <= n; i++) {
		if (p[i] == true) {
			prime.push_back(i);
		}
	}
	int prime_size = prime.size();
	prime.push_back(0);

	int cnt = 0;
	int left = 0;
	int right = 0;
	int sum = prime.front();

	while (1) {

		if (right == prime_size) break;

		if (sum > n) {
			sum -= prime[left++];
		}
		else if (sum < n) {
			sum += prime[++right];
		}
		else {
			sum += prime[++right];
			cnt++;
		}

	}

	cout << cnt;

}