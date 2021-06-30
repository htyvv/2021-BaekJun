#include<iostream>

using namespace std;

int n;
int num[] = { 1, 5 ,10, 50 };
bool visited[1000 + 1];
int answer = 0;

void DFS(int cnt, int number, int idx) {

	if (cnt == n) {
		if (visited[number]) return;
		visited[number] = true;
		answer++;
		return;
	}

	for (int i = idx; i < 4; i++) {
		DFS(cnt + 1, number + num[i], i);
	}

}

int main() {

	cin.tie(NULL);
	ios::sync_with_stdio(0);

	cin >> n;
	DFS(0, 0, 0);
	cout << answer;

	return 0;
}