#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N, L, R, X;
vector<int> score;
vector<int> result;
int r = 0;

void DFS(int depth, int idx, int count) {
	// count 개수 만큼 result 배열이 채워졌을 때,
	if (depth == count) {
		// 1. 배열의 모든 점수 합이 L과 R 사이인지 확인
		// 2. 최대값과 최소값의 차이가 X보다 큰지 확인
		int sum = 0;
		for (auto it : result) sum += it;
		if ((L <= sum && sum <= R) && (*max_element(result.begin(), result.end()) - *min_element(result.begin(), result.end()) >= X)) r++; 
		return;
	}

	for (int i = idx; i < N; i++) {
		result.push_back(score[i]);
		DFS(depth + 1, i + 1, count);
		result.pop_back();
	}

}

int main() {

	cin >> N >> L >> R >> X;

	int score_input;
	for (int i = 0; i < N; i++) {
		cin >> score_input;
		score.push_back(score_input);
	}

	for (int c = 2; c <= N; c++) DFS(0, 0, c);

	cout << r;
}