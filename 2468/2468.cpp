#include<iostream>

using namespace std;

int n;
int map[100][100];
bool check[100][100];
int dx[] = { 1,0,-1,0 };
int dy[] = { 0,1,0,-1 };

void dfs(int x, int y);

int main() {

	cin >> n;

	int input;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cin >> input;
			map[i][j] = input - n;
		}
	}

	int cnt = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (map[i][j] <= 0 || check[i][j] == true) continue;
			dfs(j, i);
			cnt++;
		}
	}

	cout << cnt;

}

void dfs(int x, int y) {
	check[y][x] = true;
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (0 >= nx && nx >= n && 0 >= ny && ny >= n) continue;
		if (map[ny][nx] > 0 && check[ny][nx] == false) {
			dfs(nx, ny);
		}

	}
}