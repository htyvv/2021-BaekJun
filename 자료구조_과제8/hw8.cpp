#include<iostream>
#include<string>

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

//-----------------------------------Stack-------------------------------------
template<class T>
class Stack {
public:
	Stack(int stackCapacity = 1000);
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
inline bool Stack<T>::IsEmpty() const { return top == -1; }

template<class T>
inline T& Stack<T>::Top() const {
	if (IsEmpty()) throw "Stack is empty. Cannot get Top";
	return stack[top];
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

//--------------------------------BinarySearchTree-----------------------------------

template <class T> class BST;  // 전방선언

template <class T>
class TreeNode {
	friend class BST<T>;
private:
	T data;
	TreeNode<T>* leftChild;
	TreeNode<T>* rightChild;
public:
	TreeNode(T d = 0, TreeNode<T>* left = 0, TreeNode<T>* right = 0) :data(d), leftChild(left), rightChild(right) {}
};

template <class T>
class BST {
private:
	TreeNode<T>* root;
	Stack<TreeNode<T>*> stack;

public:
	BST() {
		root = 0;
	}
	TreeNode<T>* const getRoot() { return root; }
	void insert(TreeNode<T>* nodes);
	void visit(TreeNode<T>* node);
	void recurInorder(TreeNode<T>* node, bool ascending);
	void ascendingOrder();
	void decendingOrder();
};



template<class T>
void BST<T>::insert(TreeNode<T>* nodes)
{
	TreeNode<T>* curr = root;
	TreeNode<T>* parent = 0;

	while (curr) {
		parent = curr;
		if (curr->data > nodes->data) curr = curr->leftChild;
		else if (curr->data < nodes->data) curr = curr->rightChild;
		else { return; }
	}

	if (root) {
		if (parent->data > nodes->data) parent->leftChild = nodes;
		else  parent->rightChild = nodes;
	}
	else root = nodes;
}

template<class T>
void BST<T>::visit(TreeNode<T>* node)
{
	cout << node->data << " ";
}

template<class T>
void BST<T>::recurInorder(TreeNode<T>* node, bool isAscending)
{	
	if (node) {
		recurInorder(node->leftChild, isAscending);
		if (isAscending) visit(node);
		else stack.Push(node);
		recurInorder(node->rightChild, isAscending);
	}	
}

template<class T>
void BST<T>::ascendingOrder()
{
	return recurInorder(root, true);
}

template<class T>
void BST<T>::decendingOrder()
{
	recurInorder(root, false);
	while (!stack.IsEmpty()) {
		TreeNode<T>* curr = stack.Top(); stack.Pop();
		visit(curr);
	}
}


int main() {

	while (true) {

		BST<int> bst;

		cout << "\n\n이진트리의 입력 값을 나열해 주세요( ! 입력 시 프로그램 종료 )\n >>> ";

		// 연결 표현으로 트리를 입력 받기
		
		while (true) {
			string input; cin >> input;

			if (input == "!") {
				cout << "\n프로그램을 종료합니다" << endl;
				return 0;
			}

			if (input == "#") break;

			else if (input == "NULL") {
				// TODO

			}
			else {
				bst.insert( new TreeNode<int>(stoi(input)) );
			}

		}
		
		// 중위 순회를 이용한 오름차순 출력
		cout << "AO : ";
		bst.ascendingOrder();
		cout << endl;

		// 중위 순회를 이용한 내름차순 출력
		cout << "DO : ";
		bst.decendingOrder();
		cout << endl;

	}

	return 0;
}

// [PDF 예제 입력]
// 30 5 2 40 80 35 #

// 내가 만든 복잡한 예제
// 1 2 3 4 NULL NULL 5 6 7 NULL NULL NULL NULL 8 9 #
// 1 2 NULL 3 NULL NULL NULL 4 NULL NULL NULL NULL NULL NULL NULL #