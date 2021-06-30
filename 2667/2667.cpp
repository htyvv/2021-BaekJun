#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>

using namespace std;

int n;
int cnt = 0;
int map[25][25];
int check[25][25];

int dx[] = { 1, 0, - 1, 0 };
int dy[] = { 0, 1, 0, -1 };

int bfs(int y, int x);

int main() {

	cin >> n;
	for (int i = 0; i < n; i++) {
		string input; cin >> input;
		for (int j = 0; j < n; j++) {
			map[i][j] = input[j] - '0';
		}
	}
	
	vector<int> result;

	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {

			if (map[y][x] > 0 && check[y][x] == false) {
				result.push_back(bfs(y, x));
				cnt++;
			}			

		}
	}

	// 출력 부분
	cout << cnt << "\n";
	// 건물 수 오름차순 정렬 후 출력
	sort(result.begin(), result.end());
	for (auto it : result) cout << it << "\n";

}

int bfs(int y, int x) {
	
	queue<pair<int, int>> q;
	int building = 1;

	q.push(make_pair(y, x));
	check[y][x] = true;

	while (!q.empty()) {

		int curr_x = q.front().second;
		int curr_y = q.front().first;

		q.pop();

		for (int i = 0; i < 4; i++) {
			int next_x = curr_x + dx[i];
			int next_y = curr_y + dy[i];
			if (0 <= next_x && next_x < n && 0 <= next_y && next_y < n) {
				if (check[next_y][next_x] == false && map[next_y][next_x] == 1) {
					q.push(make_pair(next_y, next_x));
					check[next_y][next_x] = true;
					building++;
				}	
			}
		}
	}

	return building;

}
