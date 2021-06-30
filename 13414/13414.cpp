#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

using namespace std;
typedef pair<string, int> pp;

bool cmp_students(const pp& student1, const pp& student2) {
	return student1.second < student2.second;
}

int main() {

	int k, l; cin >> k >> l;

	if (l <= k) {
		k = l;
	}

	map<string, int> students_m;

	string input;
	for(int i = 0; i < l; i++) {
		cin >> input;
		students_m[input] = i;
	}

	vector<pp> students_v(students_m.begin(), students_m.end());
	sort(students_v.begin(), students_v.end(), cmp_students);

	if (students_v.size() < k) k = students_v.size();

	for (int i = 0; i < k; i++) {
		cout << students_v[i].first << "\n";
	}

}