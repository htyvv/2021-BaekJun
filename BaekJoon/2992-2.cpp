#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// BackTracking을 위한 전역변수 선언
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

	// 재귀 호출 종료 조건
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

	// 입력 받기
	cin >> x;
	int tmp = x;

	// 입력 받은 [int형 변수 x] 를 [vector<int>형 변수 v]에 한 자리씩 저장
	while (tmp) {
		v.push_back(tmp % 10);
		tmp /= 10;
	}
	sort(v.begin(), v.end());	// 오름차순으로 정렬

	for (int i = 0; i < v.size(); i++)	is_used.push_back(false);

	func(0);	// back tracking 함수 호출
	if (!is_answer) cout << 0;	// 정답이 없는 경우 0 출력

	return 0;
}