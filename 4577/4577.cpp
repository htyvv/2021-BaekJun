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
	// ���⿡ ���� ������ �̵� X
	if (map[cy + dy[dir]][cx + dx[dir]] == '#') return;
	// ���⿡ ������� ������ �÷��̾ �̵�
	else if (map[cy + dy[dir]][cx + dx[dir]] == '.' || map[cy + dy[dir]][cx + dx[dir]] == '+') {
		if (map[cy + dy[dir]][cx + dx[dir]] == '+')
			map[cy + dy[dir]][cx + dx[dir]] = 'W';
		else map[cy + dy[dir]][cx + dx[dir]] = 'w';

		if(map[cy][cx] == 'W') 
			map[cy][cx] = '+';
		else map[cy][cx] = '.';

		cx = cx + dx[dir];  cy = cy + dy[dir];
	}
	// ���⿡ �ڽ��� ������ �ڽ��� �̵��� ������ �ִ��� Ȯ��
	else {
		// �ڽ��� �̵��� ������ �ִ��� Ȯ��
		if (map[cy + dy[dir] * 2][cx + dx[dir] * 2] == '.' || map[cy + dy[dir] * 2][cx + dx[dir] * 2] == '+') {
			// �ڽ� �̵�
			if (map[cy + dy[dir] * 2][cx + dx[dir] * 2] == '+')
				map[cy + dy[dir] * 2][cx + dx[dir] * 2] = 'B';
			else map[cy + dy[dir] * 2][cx + dx[dir] * 2] = 'b';

			// �÷��̾� �̵�
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

		// �ʱ�ȭ
		memset(map, 0, sizeof(map));

		// ��, �� �� �Է� �ޱ�
		cin >> row >> col;
		if (row == 0 && col == 0) break;

		// ���� �Է� �ޱ�
		for (int i = 0; i < row; i++) scanf("%s", map[i]);

		// �÷��̾��� ������ �Է� �ޱ�
		cin >> footprint;

		// �÷��̾��� ���� ��ġ ã��
		for (int i = 0; i < col; i++) {
			for (int j = 0; j < row; j++) {
				if (map[j][i] == 'w' || map[j][i] == 'W') {
					cx = i; cy = j;
					//if (map[j][i] == 'W') map[j][i] == '+';
				}
			}
		}

		// �����븦 ���� ���� �����ϱ�
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