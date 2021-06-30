#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp_book(const pair<string, int>& book1, const pair<string, int>& book2) {
	if (book1.second == book2.second) return book1.first < book2.first;
	return book1.second > book2.second;
}

int main() {

	int n; cin >> n;

	map<string, int> book_m;
	while (n--) {
		string input; cin >> input;
		book_m[input]++;
	}

	vector<pair<string, int>> book_v(book_m.begin(), book_m.end());
	sort(book_v.begin(), book_v.end(), cmp_book);

	cout << book_v[0].first;

}