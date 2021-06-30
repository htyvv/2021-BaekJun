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
	
	// ������ �Է¹ް� �Է� ���ǿ� �����ϴ��� �˻�
	char input[80];
	while (true) {

		cout << " �˻��� ������ �Է��� �ּ���(������ ���� �ݵ�� #�� �ٿ��ּ���)\n >>> ";
		cin.getline(input, 80, '#');

		if (strlen(input) > 80) {
			cout << " [����] 80�ڸ� �ʰ��ϴ� ������ �Է��߽��ϴ�." << endl;
			continue;
		} 

		break;
	}
	
	// ��ȣ�� ��Ȯ�� ��Ī���� �ʾ��� ��� ��� ��¿� ���� ����
	bool isError = false;
	char error[80];
	char s[40];

	// �Է� ������ �� ���ھ� Ž���ϱ�
	Stack<char> stack(40); // ��ȣ�� �ִ�� 40�� �� �� ����
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