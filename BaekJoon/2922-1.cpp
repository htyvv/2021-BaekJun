#include <iostream>
#include <algorithm>

using namespace std;

int main_2992_1() {

	ios::sync_with_stdio(false); cin.tie(NULL);

	string x; cin >> x;
	if (next_permutation(x.begin(), x.end())) 
		cout << x << endl;
	else
		cout << 0 << endl;
	
	return 0;
}