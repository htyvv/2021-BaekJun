#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// BackTracking�� ���� �������� ����
int x;
vector<int> v;
vector<int> temp;
vector<bool> is_used;
bool is_answer;

int vector_to_int(const vector<int>& vec) {
	int result = 0;
	for (auto num : vec) {
		result = result * 10 + num;
	}
	return result;
}

void func(int cnt) {

	// ��� ȣ�� ���� ����
	if (cnt == v.size()) {

		int value = vector_to_int(temp);
		if ((value > x) && !is_answer) {
			is_answer = true;
			cout << value;
		}

		return;
	}

	for (int i = 0; i < v.size(); i++) {
		if (!is_used[i]) {

			is_used[i] = true;
			temp.push_back(v[i]);

			func(cnt + 1);

			if (is_answer) return;

			is_used[i] = false;
			temp.pop_back();

		}
	}

}

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL);

	// �Է� �ޱ�
	cin >> x;
	int tmp = x;

	// �Է� ���� [int�� ���� x] �� [vector<int>�� ���� v]�� �� �ڸ��� ����
	while (tmp) {
		v.push_back(tmp % 10);
		tmp /= 10;
	}
	sort(v.begin(), v.end());	// ������������ ����

	for (int i = 0; i < v.size(); i++)	is_used.push_back(false);

	func(0);	// back tracking �Լ� ȣ��
	if (!is_answer) cout << 0;	// ������ ���� ��� 0 ���

	return 0;
}