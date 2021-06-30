#include<iostream>

using namespace std;

int arr[10000] = { 0, };

struct queue {

private:
	int bound = 0;
	int temp = 0;

public:

	void push(int x) {
		arr[bound] = x;
		bound++;
	}		

	void pop() {
		if (bound > 0) {
			cout << arr[0] << "\n";
			temp = arr[1];
			for (int i = 0; i < bound - 2; i++) {
				arr[i] = temp;
				temp = arr[i + 2];
			}
			arr[bound - 2] = temp;
			bound--;

		}
		else {
			cout << -1 << "\n";
		}
	}

	void size() {
		cout << bound << "\n";
	}

	void empty() {
		if (bound == 0) cout << 1 << "\n";
		else cout << 0 << "\n";
	}

	void front() {
		if (bound == 0) cout << -1 << "\n";
		else cout << arr[0] << "\n";
	}

	void back() {
		if (bound == 0) cout << -1 << "\n";
		else cout << arr[bound-1] << "\n";;
	}

};

int main() {

	queue q;

	int n; cin >> n;
	while (n--) {

		string input; cin >> input;
		
		if (input == "push") {
			int num; cin >> num;
			q.push(num);
		}
		else if (input == "pop") {
			q.pop();
		}
		else if (input == "size") {
			q.size();
		}
		else if (input == "empty") {
			q.empty();
		}
		else if (input == "front") {
			q.front();
		}
		else if (input == "back") {
			q.back();
		}
	}

}