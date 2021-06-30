#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<int> x;

bool cal(int mid) {

	if (x.front() - mid > 0 || x.back() + mid < n) return false;
	
	for (int i = 0; i < m-1; i++) {
		if(x[i] + mid < x[i + 1] - mid) return false;
	}

	return true;
}

int main() {

	ios::sync_with_stdio(false); 
	cin.tie(NULL);

	cin >> n >> m;
	x.resize(m);
	for (int i = 0; i < m; i++) cin >> x[i];

	int left = 1;
	int right = n;
	int ans = 0;
	while (left <= right) {
		int mid = (left + right) / 2;
		if (cal(mid)) {
			ans = mid;
			right = mid - 1;
		}
		else {
			left = mid + 1;
		}
	}
	cout << ans;

}