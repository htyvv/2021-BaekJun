#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<memory.h>

using namespace std;

int row, col;
char map[15][15];
string footprint;
int dx[] = { 0,0,-1,1 };
int dy[] = { -1,1,0,0 };
int cx, cy;

void printMap();

void move(int dir) {
	// 방향에 벽이 있으면 이동 X
	if (map[cy + dy[dir]][cx + dx[dir]] == '#') return;
	// 방향에 빈공간이 있으면 플레이어만 이동
	else if (map[cy + dy[dir]][cx + dx[dir]] == '.' || map[cy + dy[dir]][cx + dx[dir]] == '+') {
		if (map[cy + dy[dir]][cx + dx[dir]] == '+')
			map[cy + dy[dir]][cx + dx[dir]] = 'W';
		else map[cy + dy[dir]][cx + dx[dir]] = 'w';

		if(map[cy][cx] == 'W') 
			map[cy][cx] = '+';
		else map[cy][cx] = '.';

		cx = cx + dx[dir];  cy = cy + dy[dir];
	}
	// 방향에 박스가 있으면 박스가 이동할 공간이 있는지 확인
	else {
		// 박스가 이동할 공간이 있는지 확인
		if (map[cy + dy[dir] * 2][cx + dx[dir] * 2] == '.' || map[cy + dy[dir] * 2][cx + dx[dir] * 2] == '+') {
			// 박스 이동
			if (map[cy + dy[dir] * 2][cx + dx[dir] * 2] == '+')
				map[cy + dy[dir] * 2][cx + dx[dir] * 2] = 'B';
			else map[cy + dy[dir] * 2][cx + dx[dir] * 2] = 'b';

			// 플레이어 이동
			if (map[cy + dy[dir]][cx + dx[dir]] == 'B')
				map[cy + dy[dir]][cx + dx[dir]] = 'W';
			else map[cy + dy[dir]][cx + dx[dir]] = 'w';
			
			if (map[cy][cx] == 'W')
				map[cy][cx] = '+';
			else map[cy][cx] = '.';

			cx = cx + dx[dir];  cy = cy + dy[dir];
		}
	}
}

bool isFinish() {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (map[i][j] == '+' || map[i][j] == 'b') return false;
		}
	}
	return true;
}

void printMap() {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) cout << map[i][j];
		cout << "\n";
	}
}

int main() {

	int gameCount = 1;
	while (true) {

		// 초기화
		memset(map, 0, sizeof(map));

		// 행, 열 수 입력 받기
		cin >> row >> col;
		if (row == 0 && col == 0) break;

		// 지도 입력 받기
		for (int i = 0; i < row; i++) scanf("%s", map[i]);

		// 플레이어의 발자취 입력 받기
		cin >> footprint;

		// 플레이어의 시작 위치 찾기
		for (int i = 0; i < col; i++) {
			for (int j = 0; j < row; j++) {
				if (map[j][i] == 'w' || map[j][i] == 'W') {
					cx = i; cy = j;
					//if (map[j][i] == 'W') map[j][i] == '+';
				}
			}
		}

		// 발자취를 따라 게임 진행하기
		for (int i = 0; i < footprint.size(); i++) {
			switch (footprint[i]) {
			case 'U':
				move(0);
				break;
			case 'D':
				move(1);
				break;
			case 'L':
				move(2);
				break;
			case 'R':
				move(3);
				break;
			}
			if (isFinish()) {
				cout << "Game " << gameCount << ": complete" << '\n';;
				printMap();
				break;
			}
		}

		if (!isFinish()) {
			cout << "Game " << gameCount << ": incomplete" << '\n';;
			printMap();
		}
		
		gameCount++;
	}

	return 0;
}