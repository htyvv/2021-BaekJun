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

template <class T> class BST;  // ���漱��

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
		cout << "\n\n����Ʈ���� �Է� ���� ������ �ּ���( ! �Է� �� ���α׷� ���� )\n >>> ";

		// �迭ǥ������ Ʈ���� �Է� �ޱ�
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

		// Ʈ���� ���� �˻�
		for (int i = 2; i <= size; i++) {
			if (treeArray[i / 2] == INT_MIN && treeArray[i] != INT_MIN) {
				cout << "�߸��� �Է��Դϴ�. Ʈ���� ������ �ٽ� Ȯ�����ּ���.\n";
				continue;
			}
		}

		// �迭ǥ�� -> ����ǥ��
		bt.arrayToLink(treeArray, size);

		cout << "\n[  ���ȯ ������ȸ ����  ] : ";
		cout << "\n[���ȯ������ȸ ������ ��] : " << bt.NonrecInorder();

		cout << "\n[  ���ȯ ������ȸ ����  ] : ";
		cout << "\n[���ȯ������ȸ ������ ��] : " << bt.NonrecPostorder();
	}

	return 0;
}

// [PDF ���� �Է�]
// 10 20 30 NULL NULL 40 #
// 10 20 30 NULL NULL 40  NULL 50 #

// ���� ���� ������ ����
// 1 2 3 4 NULL NULL 5 6 7 NULL NULL NULL NULL 8 9 #
// 1 2 NULL 3 NULL NULL NULL 4 NULL NULL NULL NULL NULL NULL NULL # 

/* �����ϸ鼭 ���� �迭ǥ���� ���ȯ ���� ���� ��ȸ
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
	int nonRecurInorder();	// ���ȯ������ȸ�� �ϸ鼭 ���� ����ϰ� ���� ���� ���� return
	int nonRecurPostorder();// ���ȯ������ȸ�� �ϸ鼭 ���� ����ϰ� ���� ���� ���� return
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

	int currIdx = nodes; // currIdx : ���ο� ���� �迭 �ε���
	if (data.first != INT_MIN && treeArray[(currIdx-1)/2].first == INT_MIN) {
		return false; // �θ� ��尡 ������ false�� �Բ� return -> �ۿ��� fasle ���� ó��
	}

	// �������� �Է��� ���
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
	stack.Push(treeArray[i]);	// ��Ʈ���� ����
	visited[i] = true;
	while (!stack.IsEmpty()) {	// ������ ���� ���� ���� �ݺ�

		// ���� ������ ������
		while (i * 2 + 1 < nodes && treeArray[i * 2 + 1].first != INT_MIN && (!visited[i * 2 + 1])) {
			i = i * 2 + 1;
			stack.Push(treeArray[i]);
			visited[i] = true;
		}
		// ���ÿ��� ��� ���� �� �� ����� ������ ���
		if (!stack.IsEmpty()) {
			sum += stack.Top().first;
			i = stack.Top().second;
			cout << stack.Top().first << " "; stack.Pop();
		}
		// ���� ��带 ������ ���� ����� �ݺ�
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
	stack.Push(treeArray[i]);	// ��Ʈ���� ����
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
	cout << "����Ʈ���� �Է� ���� ������ �ּ���\n >>> ";
	while (true) {
		pair<int,int> value = make_pair(0, 0);
		string input; cin >> input;
		if (input == "#") break;
		if (input == "NULL") {
			value = make_pair(INT_MIN, cnt);
		}
		else value = make_pair(stoi(input), cnt);
		if (!bt.newNode(value)) {
			cout << "�߸��� �Է��Դϴ�. Ʈ���� ������ �ٽ� Ȯ�����ּ���.\n";
			return 0;
		}
		cnt++;
	}

	cout << "\n[  ���ȯ ������ȸ ����  ] : ";
	cout << "\n[���ȯ������ȸ ������ ��] : " << bt.nonRecurInorder() << endl;

	cout << "\n[  ���ȯ ������ȸ ����  ] : ";
	cout << "\n[���ȯ������ȸ ������ ��] : " << bt.nonRecurPostorder() << endl;

	return 0;
}

// [PDF ���� �Է�]
// 10 20 30 NULL NULL 40 #
// 10 20 30 NULL NULL 40  NULL 50 #

// ���� ���� ������ ����
// 5 6 7 100 NULL NULL 9 0 1 NULL NULL NULL NULL 3 8 #
*/