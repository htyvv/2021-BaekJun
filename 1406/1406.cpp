#include <iostream>
#include <list>

using namespace std;

list<char> editor;

int main() {

	string input; cin >> input;
	for (int i = 0; i < input.size(); i++) {
		editor.push_back(input[i]);
	}

	list<char>::iterator cursor = editor.end();

	int m; cin >> m;
	for (int i = 0; i < m; i++) {
		char input; cin >> input;
		if (input == 'P') {
			cin >> input;
			// 커서 왼쪽에 input추가
			editor.insert(cursor, input);
		}
		else {
			switch (input) {
			case 'L':
				// 커서를 왼쪽으로
				if (cursor != editor.begin()) cursor--;
				break;
			case 'D':
				// 커서를 오른쪽으로
				if(cursor != editor.end()) cursor++;
				break;
			case 'B':
				// 커서 왼쪽 삭제
				if (cursor != editor.begin()) {
					cursor = editor.erase(--cursor);				
				}
				break;
			}
		}
	}

	for (auto it : editor) {
		cout << it;
	}

}