#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<int> result;

void go(int cnt) {

	// ��������
	if (cnt == m) {
		for (auto it : result) {
			cout << it << " ";
		}
		cout << "\n";
		return;
	}

	// ��Ʈ��ŷ
	for (int i = 1; i <= n; i++) {
		result.push_back(i);
		go(cnt + 1);
		result.pop_back();
	}

}

int main() {

	cin >> n >> m;
	go(0);

}