#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
typedef long long ll;

int n, k;
vector<ll> lan;

int cutting(ll m) {
	ll cnt = 0;
	for (auto it : lan) {
		cnt += it / m;
	}
	return cnt;
}

int main() {

	cin >> n >> k;

	// �Է� �޴� �κ�
	ll temp;
	for (int i = 0; i < n; i++) {
		cin >> temp;
		lan.push_back(temp);
	}

	// �̺�Ž���� ���� �������� ����
	sort(lan.begin(), lan.end());

	// �̺�Ž��
	ll left = 1;
	ll right = lan.back();
	ll mid = 0;
	ll ans = 0;

	while (left <= right) {
		mid = (left + right) / 2;
		if (cutting(mid) >= k) {
			ans = mid;
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}

	cout << ans;

}