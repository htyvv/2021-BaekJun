#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n, c;
vector<int> house;

int count(int m) {
	int idx = 0;
	int cnt = 1;
	int location = house.front();
	while (location <= house.back()) {
		location += m;
		for (int i = idx; i < house.size(); i++) {
			if (location <= house[i]) {
				location = house[i];
				idx = i + 1;
				cnt++;
				break;
			}
		}		
	}
	return cnt;
}

int main() {
	
	cin >> n >> c;

	int input;
	for (int i = 0; i < n; i++) {
		cin >> input;
		house.push_back(input);
	}
	sort(house.begin(), house.end());

	int left = 1;
	int right = house.back();
	int mid = 0;
	int ans = 0;
	while (left <= right) {
		mid = (left + right) / 2;
		if (count(mid) < c) {
			right = mid - 1;
		}
		else {
			ans = mid;
			left = mid + 1;
		}
	}

	cout << ans;

}