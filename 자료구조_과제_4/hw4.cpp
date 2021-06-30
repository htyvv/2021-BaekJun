#include <iostream>
#include <string>

using namespace std;

template<class T>
void ChangeSize1D(T*& a, const int oldSize, const int newSize) {
	if (newSize < 0) throw "New length must be >= 0";
	T* temp = new T[newSize];
	int number = min(oldSize, newSize);
	copy(a, a + number, temp);
	delete[] a;
	a = temp;
}

template<class T>
class Stack {
public:
	Stack(int stackCapacity = 10);
	bool IsEmpty() const;
	T& Top() const;
	void Push(const T& item);
	void Pop();
private:
	T* stack;
	int top;
	int capacity;
};

template<class T>
Stack<T>::Stack(int stackCapacity) : capacity(stackCapacity) {
	if (capacity < 1) throw "Stack capacity must be >= 0";
	stack = new T[capacity];
	top = -1;
}

template<class T>
inline bool Stack<T>::IsEmpty() const {	return top == -1; }

template<class T>
inline T& Stack<T>::Top() const {
	if (IsEmpty()) throw "Stack is empty. Cannot get Top";
	return stack[top];
}

template<class T>
void Stack<T>::Push(const T& x) {
	if (top == capacity) {
		ChangeSize1D(stack, capacity, 2 * capacity);
		capacity *= 2;
	}
	stack[++top] = x; 
}

template<class T>
void Stack<T>::Push(const T& x) {
	if (top == capacity) {
		ChangeSize1D(stack, capacity, capacity * 2);
		capacity *= 2;
	}
	stack[++top] = x;
}

template<class T>
void Stack<T>::Pop() {
	if (IsEmpty()) throw "Stack is empty. Cannot delete";
	stack[top--].~T();
}


int main() {
	
	// 수식을 입력받고 입력 조건에 부합하는지 검사
	char input[80];
	while (true) {

		cout << " 검사할 수식을 입력해 주세요(수식의 끝에 반드시 #을 붙여주세요)\n >>> ";
		cin.getline(input, 80, '#');

		if (strlen(input) > 80) {
			cout << " [에러] 80자를 초과하는 수식을 입력했습니다." << endl;
			continue;
		} 

		break;
	}
	
	// 괄호가 정확히 매칭되지 않았을 경우 결과 출력용 변수 선언
	bool isError = false;
	char error[80];
	char s[40];

	// 입력 수식을 한 문자씩 탐색하기
	Stack<char> stack(40); // 괄호는 최대로 40개 열 수 있음
	for (int i = 0; i <= strlen(input); i++) {

		error[i] = input[i];

		if (input[i] == '(' || input[i] == '[' || input[i] == '<' || input[i] == '{') {
			stack.Push(input[i]);
		}
		if (input[i] == ')' || input[i] == ']' || input[i] == '>' || input[i] == '}') {

			try {
				stack.Top();
				if (input[i] == ')' && stack.Top() == '(') {
					stack.Pop();
				}
				else if (input[i] == ']' && stack.Top() == '[') {
					stack.Pop();
				}
				else if (input[i] == '>' && stack.Top() == '<') {
					stack.Pop();
				}
				else if (input[i] == '}' && stack.Top() == '{') {
					stack.Pop();
				}
				else {
					isError = true;
					error[i + 1] = '\0';
					break;
				}
			}
			catch (...) {
				isError = true;
				error[i + 1] = '\0';
				break;
			}

		}
	}

	if (isError) {

		cout << "\n - Error : ";
		cout << error <<endl;

		cout << " - Stack : ";
		int i = 0;
		if (stack.IsEmpty()) cout << "[Empty]";
		while (!stack.IsEmpty()) {
			s[i++] = stack.Top();
			stack.Pop();
		}
		s[i] = '\0';
		for (int i = strlen(s)-1; i >= 0; i--) cout << s[i];
		cout << endl;

	}
	else {

		if (!stack.IsEmpty()) {
			cout << "\n - Error : ";
			cout << input << endl;

			cout << " - Stack : ";
			int i = 0;
			while (!stack.IsEmpty()) {
				s[i++] = stack.Top();
				stack.Pop();
			}
			s[i] = '\0';
			for (int i = strlen(s) - 1; i >= 0; i--) cout << s[i];
			cout << endl;
		}
		else cout << "\n - Correct! " << input << endl;
		

	}

	return 0;

}