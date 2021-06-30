#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<cstring>

using namespace std;

int n, m, v;
vector<int> graph[1001];
bool check[1001] ;

void dfs(int v);
void bfs(int v);

int main() {
	
	cin >> n >> m >> v;

	int n1, n2;
	for (int i = 0; i < m; i++) {
		cin >> n1 >> n2;
		graph[n1].push_back(n2);
		graph[n2].push_back(n1);
	}

	for (int i = 1; i <= n; i++) sort(graph[i].begin(), graph[i].end());

	dfs(v);
	cout << endl;
	
	memset(check, false, sizeof(check));

	bfs(v);
	cout << endl;

}

void dfs(int v) {
	cout << v << " ";
	check[v] = true;
	for (auto next : graph[v]) {
		if (check[next] == false) {
			dfs(next);
		}
	}
}
void bfs(int v) {
	
	queue<int> q;
	check[v] = true;
	q.push(v);

	while (!q.empty()) {

		int curr = q.front();
		cout << curr << " ";
		q.pop();
		
		for (auto next : graph[curr]) {
			if (check[next] == false) {
				check[next] = true;
				q.push(next);	
			}
		}
	
	}

}