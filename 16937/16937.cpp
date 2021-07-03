#include <iostream>
#include <vector>

using namespace std;

int h, w, n;
vector<int> r;
vector<int> c;

bool inRectangle(int idx1, int idx2) {
	if (
		(r[idx1] + r[idx2] <= h && max(c[idx1], c[idx2]) <= w) ||
		(c[idx1] + c[idx2] <= w && max(r[idx1], r[idx2]) <= h) ||
		(r[idx1] + c[idx2] <= h && max(c[idx1], r[idx2]) <= w) ||
		(c[idx1] + r[idx2] <= w && max(r[idx1], c[idx2]) <= h)
		) return true;
	return false;
}

int main() {


	cin >> h >> w >> n;
	for (int i = 0; i < n; i++) {
		int input_r, input_c; cin >> input_r >> input_c;
		r.push_back(input_r);
		c.push_back(input_c);
	}
	
	int max_area = -1;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (inRectangle(i, j)) {
				max_area = max(max_area, (r[i] * c[i]) + (r[j] * c[j]));
			}
		}
	}

	if (max_area == -1) max_area = 0;
	cout << max_area << endl;

	return 0;
}