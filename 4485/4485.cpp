#include<iostream>
#include<queue>

int n;

int map[125][125];

int dx[] = { 1,0,-1,0 };
int dy[] = { 0,1,0,-1 };

using namespace std;

int main() {

	while (1) {
		cin >> n;
		if (n == 0) break;

		for (int y = 0; y < n; y++) {
			for (int x = 0; x < n; x++) {
				cin >> map[y][x];
			}
		}



	}

}
