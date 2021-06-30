#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

int belt[503][503];

// [direction] 1 : 왼쪽, 2 : 아래, 3: 오른쪽, 4: 위
void tornado(int x, int y, int direction) {

	int sand = belt[y][x];
	int dy[10];
	int dx[10];
	double div[9];

	if (direction == 1) {
		int temp_dy[] = { y + 1, y - 1, y + 1, y - 1, y + 2, y - 2, y + 1, y - 1, y, y };
		int temp_dx[] = { x + 1, x + 1, x, x, x, x, x - 1, x - 1, x - 2, x - 1 };
		double temp_div[] = { 0.01, 0.01, 0.07, 0.07, 0.02, 0.02, 0.1, 0.1, 0.05 };
		copy(temp_dy, temp_dy + 10, dy);
		copy(temp_dx, temp_dx + 10, dx);
		copy(temp_div, temp_div + 9, div);
	}

	else if (direction == 2) {
		int temp_dy[] = { y - 1, y - 1, y, y, y, y, y + 1, y + 1, y + 2, y + 1 };
		int temp_dx[] = { x + 1, x - 1, x + 1, x - 1, x + 2, x - 2, x + 1, x - 1, x, x };
		double temp_div[] = { 0.01, 0.01, 0.07, 0.07, 0.02, 0.02, 0.1, 0.1, 0.05 };
		copy(temp_dy, temp_dy + 10, dy);
		copy(temp_dx, temp_dx + 10, dx);
		copy(temp_div, temp_div + 9, div);
	}

	else if (direction == 3) {
		int temp_dy[] = { y + 1, y - 1, y + 1, y - 1, y + 2, y - 2, y + 1, y - 1, y, y };
		int temp_dx[] = { x - 1, x - 1, x, x, x, x, x + 1, x + 1, x + 2, x + 1 };
		double temp_div[] = { 0.01, 0.01, 0.07, 0.07, 0.02, 0.02, 0.1, 0.1, 0.05 };
		copy(temp_dy, temp_dy + 10, dy);
		copy(temp_dx, temp_dx + 10, dx);
		copy(temp_div, temp_div + 9, div);
	}

	else {
		int temp_dy[] = { y + 1, y + 1, y, y, y, y, y - 1, y - 1, y - 2, y - 1 };
		int temp_dx[] = { x + 1, x - 1, x + 1, x - 1, x + 2, x - 2, x + 1, x - 1, x, x };
		double temp_div[] = { 0.01, 0.01, 0.07, 0.07, 0.02, 0.02, 0.1, 0.1, 0.05 };
		copy(temp_dy, temp_dy + 10, dy);
		copy(temp_dx, temp_dx + 10, dx);
		copy(temp_div, temp_div + 9, div);
	}
	
	int alpha = sand;
	for (int i = 0; i < 9; i++) {
		belt[dy[i]][dx[i]] += floor(sand * div[i]);
		alpha -= floor(sand * div[i]);
	}
	belt[dy[9]][dx[9]] += alpha;
	belt[y][x] = 0;
};

int main() {

	// 격자 크기 입력
	int n; cin >> n;

	// 초기 모래의 양 배열 a 입력
	for (int i = 2; i < n+2; i++) {
		for (int j = 2; j < n+2; j++) {
			cin >> belt[i][j];
		}
	}

	int r = n / 2 + 2;
	int c = n / 2 + 2;

	// 11 22 33 44 55 ... (2,2) 도착

	for (int length = 1; length <= n; length++) {

		// 마지막 이동(종료)
		if (length == n) {
			while (c != 2) {
				tornado(--c,r,1);			
			}
			break;
		}

		// 왼쪽 -> 아래
		if (length % 2 == 1) {
			// 토네이도 왼쪽 이동
			for(int k = 0; k < length; k++)	tornado(--c, r, 1);
			// 토네이도 아래 이동
			for (int k = 0; k < length; k++) tornado(c, ++r, 2);
		}
		// 오른쪽 -> 위
		else {
			// 토네이도 오른쪽 이동
			for (int k = 0; k < length; k++) tornado(++c, r, 3);
			// 토네이도 위 이동
			for (int k = 0; k < length; k++) tornado(c, --r, 4);
		}

	}

	// 최종적으로 영역 밖의 모래 양 더하기

	int sum = 0;

	for (int i = 0; i < n + 4; i++) {	
			for (int j = 0; j < n + 4; j++) {
				if ((2 <= i && i <= n + 1)&&(2 <= j && j <= n + 1)) continue;
				sum += belt[j][i];
			}
	}

	cout << sum;

}