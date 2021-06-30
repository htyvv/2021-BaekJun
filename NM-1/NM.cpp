#include <iostream>
#include <vector>

using namespace std;

int n, m;
bool is_used[10];
vector<int> temp;

void back_tracking(int cnt) {

	if (cnt == m) {

		for (auto n : temp) {
			cout << n << " ";
		}
		cout << "\n";

		return;
	}

	for (int i = 1; i <= n; i++) {

		if (!is_used[i]) {

			is_used[i] = true;
			temp.push_back(i);

			back_tracking(cnt + 1);

			is_used[i] = false;
			temp.pop_back();
		}

	}


}

int main() {

	cin >> n >> m;

	back_tracking(0);

	return 0;
}