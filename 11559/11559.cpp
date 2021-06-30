#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;

char board[12][6];
char temp[12][6];
bool check[12][6];

int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1};


void bfs(int y, int x);

int main() {

	// board 입력 받기
	for (int r = 0; r < 12; r++) {
		string input; cin >> input;
		for (int c = 0; c < 6; c++) {
			board[r][c] = input[c];
		}
	}

	// 더이상 터질 수 있는 뿌요가 없을때 까지 반복
	int cnt = 0;


		memset(check, false, sizeof(check));
		//copy(board, board + 72, temp);

		//bfs 실행 -> bfs 하면서 같은색 4개 이상이면 . 으로 바꾼다
		for (int y = 0; y < 12; y++) {
			for (int x = 0; x < 6; x++) {
				if (board[y][x] != '.' && check[y][x] == false)
					bfs(y, x);
			}
		}
		// 중력의 방향으로 뿌요를 떨어트린다.

		//if (equal(board, temp, board + 72)) break;
		cnt++;

		for (int y = 0; y < 12; y++) {
			for (int x = 0; x < 6; x++) {
				
				cout << board[y][x];
			}
			cout << endl;
		}
	
	cout << cnt;

}

void bfs(int y, int x) {

	char color = board[y][x];
	vector<pair<int, int>> list;
	list.push_back(make_pair(y, x));
	int cnt = 1;

	queue<pair<int, int>> q;
	q.push(make_pair(y, x));
	check[y][x] = true;
	//board[y][x] = '.';

	while (!q.empty()) {

		int curr_x = q.front().second;
		int curr_y = q.front().first;
		
		q.pop();

		for (int i = 0; i < 4; i++) {

			int next_x = curr_x + dx[i];
			int next_y = curr_y + dy[i];
			if (0 <= next_x && next_x < 6 && 0 <= next_y && next_y < 12) {
				if (board[next_y][next_x] == color && check[next_y][next_x] == false) {
					q.push(make_pair(next_y, next_x));
					check[next_y][next_x] = true;
					cnt++;
					list.push_back(make_pair(next_y, next_x));
				}
			}
		}

		if (cnt >= 4) {
			for (auto it : list) {
				board[it.first][it.second] = '.';
			}
		}

	}
}

