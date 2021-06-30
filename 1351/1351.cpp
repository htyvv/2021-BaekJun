#include <iostream>
#include <vector>

typedef long long ll;
using namespace std;

int main() {

	ll n, p, q; cin >> n >> p >> q;

	ll temp;
	vector<ll> arr; arr.push_back(1);
	for (ll i = 1; i <= n; i++) {
		temp = arr[i / p] + arr[i / q];
		arr.push_back(temp);
	}
	
	cout << arr[n];

}