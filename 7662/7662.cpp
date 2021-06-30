#include<iostream>
#include<queue>

using namespace std;

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL);

	int test_case; cin >> test_case;

	while (test_case--) {

		priority_queue<int, vector<int>, less<int>> max_heap;
		priority_queue<int, vector<int>, greater<int>> min_heap;

		int command; cin >> command;

		while(command--) {

			char operation; cin >> operation;
			int num; cin >> num;

			switch (operation) {

			case 'I':
				max_heap.push(num);
				min_heap.push(num);
				break;

			case 'D':

				switch (num) {

				case 1:
					if (!max_heap.empty()) max_heap.pop();
					break;
				
				case -1:
					if (!min_heap.empty()) min_heap.pop();
					break;
				}

				break;

			}

		}

		// 남은 큐의 최대 최소 출력
		if (!max_heap.empty() && !min_heap.empty()) {
			if (max_heap.top() != min_heap.top()) 
				cout << max_heap.top() << " " << min_heap.top() << "\n";
			else cout << "EMPTY" << "\n";
		}
		else cout << "EMPTY" << "\n";
	}

}