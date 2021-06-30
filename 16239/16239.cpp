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

	// �ʱ�ȭ
	edible_list.clear();

	// ���� �� �ִ� ������� ���� ����ϰ� ��ǥ�� ����Ʈ�� �����Ѵ�.
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
						// �԰� �� �� ��Ȳ ����
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

	// �Է� �ޱ�
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			cin >> bowl[y][x];
			// �Ʊ� ����� ���� ��ġ ����
			if (bowl[y][x] == 9) shark_pos = make_pair(y, x);
		}
	}

	int time = 0;

	while (1) {

		// ���� �� �ִ� ����� �� �ľ�
		edible_num = check();

		//  ���ٸ� ����
		if (edible_num == 0) break;

		// 1������ �ٷ� ������ ��
		else if (edible_num == 1) {
			// �Դ� �Լ� (���� ��� ��ġ�� ��� list�� front�� ��ǥ)
			// ��� ��ġ���� ��ǥ �������� �ִܰŸ� ��ŭ �ð��� ���ϰ�,
			// ������ ��� ��ġ�� 0���� ���� ������� ��ġ�� 9��
			time += eat(shark_pos.first, shark_pos.second);
		}

		// 1�������� ������ ����� ����� Ž��(�켱���� : �����, ��, ���� ��)
		else {
			// �켱������ �����ϴ� ����� ���� (list�� �� �����ؼ� front�� �켱���� 1���� ����)
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
			// �Դ� �Լ�
			time += eat(shark_pos.first, shark_pos.second);
		}
	}

	cout << time;

}