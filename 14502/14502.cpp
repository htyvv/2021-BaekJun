#include<iostream>
#include<cstring>
#include<queue>
#include<ctime>

using namespace std;

int n, m;
int result;

int map[8][8];
int virus_map[8][8];

vector<pair<int, int>> virus_pos;

int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };

int safe_area() {
	int cnt = 0;
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			if (virus_map[y][x] == 0) cnt++;
		}
	}
	return cnt;
}

void spread_virus() {

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			virus_map[i][j] = map[i][j];

	queue<pair<int, int>> q;
	for (auto it : virus_pos) q.push(make_pair(it.first, it.second));				
	
	while (!q.empty()) {
		int cy = q.front().first;
		int cx = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++) {
			int ny = cy + dy[i];
			int nx = cx + dx[i];
			if (0 <= nx && nx < m && 0 <= ny && ny < n) {
				if (virus_map[ny][nx] == 0) {
					virus_map[ny][nx] = 2;
					q.push(make_pair(ny, nx));
				}
			}
		}
	}

	result = max(safe_area(), result);
}

void make_wall(int cnt) {

	if (cnt == 3) {
		// ���̷��� ��Ʈ����
		spread_virus();
		return;
	}

	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			if (map[y][x] == 0) {
				map[y][x] = 1;			
				make_wall(cnt + 1);
				map[y][x] = 0;			
			}
		}
	}

}

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL);

	//time_t start, end;
	//start = time(NULL);

	cin >> n >> m;

	// ���� �Է� �ޱ�
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			cin >> map[y][x];
			if (map[y][x] == 2) virus_pos.push_back(make_pair(y, x));
		} 
	}

	// dfs ��Ʈ��ŷ���� ���� ( �� 3�� ���� �ݺ� )
	make_wall(0);

	// ��� ���
	cout << result;

	//end = time(NULL);
	//cout << "\ntime : " << (double)end - start;

}