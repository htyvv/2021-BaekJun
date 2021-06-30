#include<iostream>
#include<string>
#include<limits>

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

//-------------------------------------Stack----------------------------------------
template<class T>
class Stack {
public:
	Stack(int stackCapacity = 100);
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
		ChangeSize1D(stack, capacity, 2 * capacity);
		capacity *= 2;
	}
	stack[++top] = x;
}

template<class T>
void Stack<T>::Pop() {
	if (IsEmpty()) throw "Stack is empty. Cannot delete";
	stack[top--].~T();
}

//-----------------------------------BinaryTree--------------------------------------

template <class T> class BST;  // 전방선언

template <class T>
class TreeNode {
    friend class BST<T>;
private :
	T data;
    TreeNode<T>* leftChild;
    TreeNode<T>* rightChild;
public :
    TreeNode(T d = 0, TreeNode<T>* left = 0, TreeNode<T>* right = 0) :data(d), leftChild(left), rightChild(right) {}
};

template <class T>
class BST {
private:
    TreeNode<T>* root;

public:
    BST() {
        root = 0;
    }
	void Visit(TreeNode<T>* node );
    int NonrecInorder();
	int NonrecPostorder();
	void arrayToLink(T* array, int size);
};

template<class T>
void BST<T>::Visit(TreeNode<T>* node)
{
	cout << node->data << " ";
}

template<class T>
int BST<T>::NonrecInorder()
{
	int sum = 0;
	Stack<TreeNode<T>*> stack;
	TreeNode<T>* currNode = root;
	while (true) {
		while (currNode) {
			stack.Push(currNode);
			currNode = currNode->leftChild;
		}
		if (stack.IsEmpty()) return sum;
		currNode = stack.Top(); stack.Pop();
		if (currNode->data != INT_MIN) {
			Visit(currNode);
			sum += currNode->data;
		}
		currNode = currNode->rightChild;
	}
}

template<class T>
int BST<T>::NonrecPostorder()
{
	int sum = 0;
	Stack<TreeNode<T>*> stack, result;

	stack.Push(root);
	TreeNode<T>* currNode;

	while (!stack.IsEmpty()) {

		currNode = stack.Top(); stack.Pop();
		result.Push(currNode);

		if (currNode->leftChild)
			stack.Push(currNode->leftChild);
		if (currNode->rightChild)
			stack.Push(currNode->rightChild);
	}

	while (!result.IsEmpty()) {
		currNode = result.Top(); result.Pop();
		if (currNode->data != INT_MIN) {
			Visit(currNode);
			sum += currNode->data;
		}
	}

	return sum;
}

template<class T>
void BST<T>::arrayToLink(T* arr, int size)
{
	TreeNode<int>* nodes = new TreeNode<int>[size + 1];
	for (int i = 1; i <= size; i++) {
		nodes[i].data = arr[i];
		nodes[i].leftChild = NULL;
		nodes[i].rightChild = NULL;
	}
	for (int i = 2; i <= size; i++) {
		if (i % 2 == 0) {
			nodes[i / 2].leftChild = &nodes[i];
		}
		else {
			nodes[i / 2].rightChild = &nodes[i];
		}
	}
	root = &nodes[1];
}



int main() {

	while (true) {
		BST<int> bt;
		int treeArray[1000];
		cout << "\n\n이진트리의 입력 값을 나열해 주세요( ! 입력 시 프로그램 종료 )\n >>> ";

		// 배열표현으로 트리를 입력 받기
		int idx = 1;
		while (true) {
			string input; cin >> input;
			if (input == "!") return 0;
			if (input == "#") break;
			else if (input == "NULL") {
				treeArray[idx++] = INT_MIN;
			}
			else treeArray[idx++] = stoi(input);
		}
		int size = idx - 1;

		// 트리의 오류 검사
		for (int i = 2; i <= size; i++) {
			if (treeArray[i / 2] == INT_MIN && treeArray[i] != INT_MIN) {
				cout << "잘못된 입력입니다. 트리의 구조를 다시 확인해주세요.\n";
				continue;
			}
		}

		// 배열표현 -> 연결표현
		bt.arrayToLink(treeArray, size);

		cout << "\n[  비순환 중위순회 순서  ] : ";
		cout << "\n[비순환중위순회 정수의 합] : " << bt.NonrecInorder();

		cout << "\n[  비순환 후위순회 순서  ] : ";
		cout << "\n[비순환후위순회 정수의 합] : " << bt.NonrecPostorder();
	}

	return 0;
}

// [PDF 예제 입력]
// 10 20 30 NULL NULL 40 #
// 10 20 30 NULL NULL 40  NULL 50 #

// 내가 만든 복잡한 예제
// 1 2 3 4 NULL NULL 5 6 7 NULL NULL NULL NULL 8 9 #
// 1 2 NULL 3 NULL NULL NULL 4 NULL NULL NULL NULL NULL NULL NULL # 

/* 뻘짓하면서 만든 배열표현의 비순환 중위 후위 순회
#include<iostream>
#include<string>
#include<limits>

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

//-------------------------------------Stack----------------------------------------
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
inline bool Stack<T>::IsEmpty() const { return top == -1; }

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
void Stack<T>::Pop() {
	if (IsEmpty()) throw "Stack is empty. Cannot delete";
	stack[top--].~T();
}


//----------------------------------BinaryTreeByArray-----------------------------------
class BinaryTree {
	//friend istream& operator>> (istream& is, BinaryTree& b);
	//friend ostream& operator<< (ostream& os, BinaryTree& b);
public :
	BinaryTree() : capacity(10), nodes(0) {
		treeArray = new pair<int, int>[capacity];
	}
	int nonRecurInorder();	// 비순환중위순회를 하면서 값을 출력하고 정수 값의 합을 return
	int nonRecurPostorder();// 비순환후위순회를 하면서 값을 출력하고 정수 값의 합을 return
	bool newNode(pair<int, int> data);
private :
	pair<int, int>* treeArray;
	int capacity;
	int nodes;
};

bool BinaryTree::newNode(pair<int, int> data) {

	if (capacity == nodes) {
		ChangeSize1D(treeArray, capacity, 2 * capacity);
		capacity *= 2;
	}

	int currIdx = nodes; // currIdx : 새로운 값의 배열 인덱스
	if (data.first != INT_MIN && treeArray[(currIdx-1)/2].first == INT_MIN) {
		return false; // 부모 노드가 없으면 false와 함께 return -> 밖에서 fasle 예외 처리
	}

	// 정상적인 입력의 경우
	treeArray[currIdx] = data;
	nodes++;
	return true;

}

int BinaryTree::nonRecurInorder() {
	int sum = 0;
	Stack<pair<int, int>> stack;
	bool* visited = new bool[nodes];
	fill(visited, visited + nodes, false);
	int i = 0;
	stack.Push(treeArray[i]);	// 루트부터 시작
	visited[i] = true;
	while (!stack.IsEmpty()) {	// 스택이 비지 않은 동안 반복

		// 왼쪽 끝까지 내려감
		while (i * 2 + 1 < nodes && treeArray[i * 2 + 1].first != INT_MIN && (!visited[i * 2 + 1])) {
			i = i * 2 + 1;
			stack.Push(treeArray[i]);
			visited[i] = true;
		}
		// 스택에서 노드 삭제 후 그 노드의 데이터 출력
		if (!stack.IsEmpty()) {
			sum += stack.Top().first;
			i = stack.Top().second;
			cout << stack.Top().first << " "; stack.Pop();
		}
		// 현재 노드를 오른쪽 노드로 만들고 반복
		if (i * 2 + 2 < nodes && treeArray[i * 2 + 2].first != INT_MIN && (!visited[i * 2 + 2])) {
			i = i * 2 + 2;
			stack.Push(treeArray[i]);
			visited[i] = true;
		}
	}

	return sum;
}

int BinaryTree::nonRecurPostorder() {
	int sum = 0;
	Stack<pair<int, int>> stack;
	bool* visited = new bool[nodes];
	fill(visited, visited + nodes, false);
	int i = 0;
	stack.Push(treeArray[i]);	// 루트부터 시작
	while (!stack.IsEmpty()) {
		i = stack.Top().second;
		if (i * 2 + 1 < nodes && treeArray[i * 2 + 1].first != INT_MIN && (!visited[i * 2 + 1])) {
			i = i * 2 + 1;
			stack.Push(treeArray[i]);
		}
		else {
			if (i * 2 + 2 < nodes && treeArray[i * 2 + 2].first != INT_MIN && (!visited[i * 2 + 2])) {
				i = i * 2 + 2;
				stack.Push(treeArray[i]);
			}
			else {
				sum += stack.Top().first;
				cout << stack.Top().first << " "; stack.Pop();
				visited[i] = true;
			}
		}
	}


	return sum;
}

int main() {

	BinaryTree bt;
	int cnt = 0;
	cout << "이진트리의 입력 값을 나열해 주세요\n >>> ";
	while (true) {
		pair<int,int> value = make_pair(0, 0);
		string input; cin >> input;
		if (input == "#") break;
		if (input == "NULL") {
			value = make_pair(INT_MIN, cnt);
		}
		else value = make_pair(stoi(input), cnt);
		if (!bt.newNode(value)) {
			cout << "잘못된 입력입니다. 트리의 구조를 다시 확인해주세요.\n";
			return 0;
		}
		cnt++;
	}

	cout << "\n[  비순환 중위순회 순서  ] : ";
	cout << "\n[비순환중위순회 정수의 합] : " << bt.nonRecurInorder() << endl;

	cout << "\n[  비순환 후위순회 순서  ] : ";
	cout << "\n[비순환후위순회 정수의 합] : " << bt.nonRecurPostorder() << endl;

	return 0;
}

// [PDF 예제 입력]
// 10 20 30 NULL NULL 40 #
// 10 20 30 NULL NULL 40  NULL 50 #

// 내가 만든 복잡한 예제
// 5 6 7 100 NULL NULL 9 0 1 NULL NULL NULL NULL 3 8 #
*/