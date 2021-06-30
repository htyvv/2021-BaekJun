#include <iostream>
#include <deque>
#include <algorithm>

using namespace std;

int main() {

	int n; cin >> n;
	deque<int> divisors;

	int temp;
	while (n--) {
		cin >> temp;
		divisors.push_back(temp);
	}

	sort(divisors.begin(), divisors.end());

	cout << divisors.front() * divisors.back();

}