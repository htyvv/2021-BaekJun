#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<int> v;

// ���� ���� ���
void print() {
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}
	cout << "\n";
}

// ��Ʈ��ŷ
void go(int cnt) {

	// ��������
	if (cnt == m) {
		print();
		return;
	}

	for (int i = 1; i <= n; i++) {
		if(!v.empty() && i < v.back()){
			continue;
		}
		else {
			v.push_back(i);
			go(cnt + 1);
			v.pop_back();
		}
	}

}

int main() {
	cin >> n >> m;
	go(0);
	return 0;
}