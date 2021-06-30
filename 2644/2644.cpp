#include<iostream>
#include<vector>
#include<queue>

using namespace std;

vector<int> family[101];
int check[101];
int dist[101];

int relationship(int t1, int t2) {

	queue<int> q;
	q.push(t1);
	dist[t1] = 0;
	check[t1] = true;
	
	while (!q.empty()) {
		int curr = q.front();
		q.pop();
		for (auto next : family[curr]) {
			if (check[next] == false) {
				q.push(next);
				check[next] = true;
				dist[next] = dist[curr] + 1;
				// Ŀ��
				if (next == t2) return dist[next];
			}
		}
	}
	return -1;
}

int main() {

	// �Է� �ޱ�
	int n; cin >> n;
	int t1, t2; cin >> t1 >> t2;
	int m; cin >> m;
	int parent, child;
	for (int i = 0; i < m; i++) {
		cin >> parent; cin >> child;
		family[parent].push_back(child);
		family[child].push_back(parent);
	}

	// bfs �� ��� ���
	cout << relationship(t1, t2);



}