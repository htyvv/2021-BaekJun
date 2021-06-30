#include<iostream>
#include<cstring>
#include<vector>

using namespace std;

int m, n, k;
int v[50][50];
bool check[50][50];

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

void dfs(int x, int y);
void init();

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL);

	int t; cin >> t;

	while (t--) {

		cin >> m >> n >> k;
		init();

		int x, y;
		for (int i = 0; i < k; i++) {
			cin >> x >> y;
			v[y][x] = 1;

		} 

		int cnt = 0;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {

				if (check[j][i] == true || v[j][i] == 0) continue;
				dfs(i, j);
				cnt++;
			}
		}

		cout << cnt << "\n";

	}

}

void init() {
	memset(v, 0, sizeof(v));
	memset(check, false, sizeof(check));
}

void dfs(int x, int y) {
	check[y][x] = true;
	for (int i = 0; i < 4; i++) {
		int next_x = x + dx[i];
		int next_y = y + dy[i];
		if (next_y < 0 || next_y >= n || next_x < 0 || next_x >= m)
			continue;
		if (check[next_y][next_x] == false && v[next_y][next_x] == 1)
			dfs(next_x, next_y);
	}
}