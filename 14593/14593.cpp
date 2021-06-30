#include <iostream>
#include <algorithm>

using namespace std;

class student {
public:
	int s, c, l, idx;
};

student students[1000];

bool comp(student& front, student& back) {
	if (front.s == back.s) {
		if (front.c == back.c) {
			return front.l < back.l;
		}
		else return front.c < back.c;
	}
	else return front.s > back.s;
}

int main() {

	int n;

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> students[i].s >> students[i].c >> students[i].l;
		students[i].idx = i + 1;
	}

	sort(students, students + n, comp);

	cout << students[0].idx;

}