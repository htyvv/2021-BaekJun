#include<iostream>
#include<cstring>
#include<climits>
#include<queue>

using namespace std;

int n;
int result;
pair<int, int> shark_pos;
int shark_size = 2;
int eat_cnt;

vector<pair<int, int>> edible_list;
int edible_num;

int bowl[20][20];
int visited[20][20];
int dist[20][20];

int dx[] = {  0, -1, 0, 1 };
int dy[] = { -1, 0, 1, 0 };

int check() {

	// 초기화
	edible_list.clear();

	// 먹을 수 있는 물고기의 수를 계산하고 좌표를 리스트에 저장한다.
	int cnt = 0;
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			if (0 < bowl[y][x] && shark_size > bowl[y][x] && bowl[y][x] != 9) {
				edible_list.push_back(make_pair(y, x));
				cnt++;
			}
		}
	}
	return cnt;
}

int eat(int sy, int sx) {

	memset(dist, 0, sizeof(dist));
	memset(visited, false, sizeof(visited));

	queue<pair<int, int>> q;
	q.push(make_pair(sy, sx));
	visited[sy][sx] = true;

	while (!q.empty()) {
		int cy = q.front().first;
		int cx = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++) {
			int ny = cy + dy[i];
			int nx = cx + dx[i];
			if (0 <= nx && nx < n && 0 <= ny && ny < n) {
				if (bowl[ny][nx] <= shark_size && !visited[ny][nx]) {
					q.push(make_pair(ny, nx));
					visited[ny][nx] = true;
					dist[ny][nx] = dist[cy][cx] + 1;
					if (ny == edible_list.front().first && nx == edible_list.front().second) {
						// 먹고 난 후 상황 수정
						eat_cnt++;
						if (eat_cnt == shark_size) {
							shark_size++;
							eat_cnt = 0;
						}

						bowl[sy][sx] = 0;
						bowl[edible_list.front().first][edible_list.front().second] = 9;
						shark_pos = make_pair(edible_list.front().first, edible_list.front().second);
						
						return dist[ny][nx];
					}					
				}
			}
		}
	}
	return 0;
}

int find_dist(int sy, int sx, pair<int, int> p) {

	memset(dist, 0, sizeof(dist));
	memset(visited, false, sizeof(visited));

	queue<pair<int, int>> q;
	q.push(make_pair(sy, sx));
	visited[sy][sx] = true;

	while (!q.empty()) {
		int cy = q.front().first;
		int cx = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++) {
			int ny = cy + dy[i];
			int nx = cx + dx[i];
			if (0 <= nx && nx < n && 0 <= ny && ny < n) {
				if (bowl[ny][nx] <= shark_size && !visited[ny][nx]) {
					q.push(make_pair(ny, nx));
					visited[ny][nx] = true;
					dist[ny][nx] = dist[cy][cx] + 1;
					if (ny == p.first && nx == p.second) {
						return dist[ny][nx];
					}
				}
			}
		}
	}
	return 0;
}

int main() {

	cin >> n;

	// 입력 받기
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			cin >> bowl[y][x];
			// 아기 상어의 현재 위치 저장
			if (bowl[y][x] == 9) shark_pos = make_pair(y, x);
		}
	}

	int time = 0;

	while (1) {

		// 먹을 수 있는 물고기 수 파악
		edible_num = check();

		//  없다면 종료
		if (edible_num == 0) break;

		// 1마리면 바로 먹으러 감
		else if (edible_num == 1) {
			// 먹는 함수 (현재 상어 위치가 출발 list의 front가 목표)
			// 상어 위치부터 목표 물고기까지 최단거리 만큼 시간에 더하고,
			// 기존의 상어 위치를 0으로 먹힌 물고기의 위치를 9로
			time += eat(shark_pos.first, shark_pos.second);
		}

		// 1마리보다 많으면 가까운 물고기 탐색(우선순위 : 가까움, 위, 왼쪽 순)
		else {
			// 우선순위에 부합하는 물고기 선정 (list를 잘 조작해서 front에 우선순위 1등을 남김)
			pair<int, int> next = make_pair(0, 0);
			int dist = INT_MAX;
			for (auto target : edible_list) {
				int temp = find_dist(shark_pos.first, shark_pos.second, target);
				if (temp < dist) {
					dist = temp;
					next = make_pair(target.first, target.second);
				}
			}
			edible_list.clear();
			edible_list.push_back(next);
			// 먹는 함수
			time += eat(shark_pos.first, shark_pos.second);
		}
	}

	cout << time;

}