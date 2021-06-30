#include<iostream>
#include<queue>

using namespace std;

int board[300][300];
int dis[300][300];
bool check[300][300];

int dx[] = {1, 2, 2, 1, -1, -2, -2, -1};
int dy[] = {-2, -1, 1, 2, 2, 1, -1, -2};

int result;
int l;
pair<int, int> s;
pair<int, int> d;

void bfs(int cnt, int x, int y);

int main() {

	int t; cin >> t;

	while (t--) {

		result = 0;
		cin >> l;
		cin >> s.first >> s.second;
		cin >> d.first >> d.second;

		bfs(s.first, s.second);

		cout << result << "\n";

	}

}

void bfs( int x, int y) {



	for (int i = 0; i < 8; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (!(0 <= nx && nx <= l && 0 <= ny && ny <= l)) continue;
		check[ny][nx] = true;
		bfs(cnt + 1, nx, ny);
		check[ny][nx] = false;	
	}

}