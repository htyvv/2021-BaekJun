#include <iostream>
#include <string>

using namespace std;

template<class T> class CircularListWithHeader;	// ���� ����

//-----------------------ChainNode-------------------------
template<class T> class Node {
	template<class U> friend class Chain;
public : 
	Node(T d, Node* l) : data(d), link(l) {}
private :
	T data;
	Node* link;
};
//-------------------------Chain---------------------------
template<class T>
class CircularListWithHeader {
public :
	// ������
	CircularListWithHeader() : first(0) {}
	// �ݺ���
	class Iterator {
	public:
		//������
		Iterator(Node<T>* start) { current = start; }
		// ������ ������
		T& operator*() const { return current->data; }
		T* operator->() const { return &current->data; }
		// ����
		Iterator& operator++() { current = current->link; return *this; }
		Iterator& operator++(int) {
			Iterator old = *this;
			current = current->link;
			return old;
		}
		// ���� �˻�
		bool operator!=(const Iterator right) { return current != right.current; }
		bool operator==(const Iterator right) { return current == right.current; }
	private:
		Node<T>* current;
	};

	// ü�� ���� �����
	Iterator begin() { return iterator(first); }	// ����Ʈ�� ù ��° ��� ��ġ
	Iterator end() { return iterator(0); }	// ����Ʈ�� �� ������ ��带 �ϳ� ���� ��ġ
	void InsertFront(T& data) { first = new Node<T>(data, first); }
private :
	Node<T>* first;
};



int main() {

	CircularListWithHeader<int> chain;
	CircularListWithHeader<int> temp;

	cout << "\t[���α׷� �Ұ�]\n" << "���ϴ� ���� ��ŭ ������ �Է��մϴ�.\n�� �̻� �Է��� ��ġ ������ #�� �Է��մϴ�.\n�Էµ� ��� ���Ҹ� ������� ����ϰ� �ּҰ��� ã�� ����մϴ�.\n\n";

	// ���� ����Ʈ �Է� �ޱ� > ü������
	while (true) {
		cout << "\nü�ο� �߰��� ������ �Է��� �ּ���\n>>> ";
		string input; getline(cin, input);
		if (input == "#") break;
		try {
			int num = stoi(input);
			chain.InsertFront(num);
		}
		catch (exception e) {
			cout << "�߸��� �Է��Դϴ�. �ٽ� �Է��� �ּ���" << endl;
			continue;
		}		
	}

	// ���� ü���� ��� ���Ҹ� ��� (ü�� �ݺ��� ���)
	cout << "\n - ��� ���� ��� : ";
	for (CircularListWithHeader<int>::Iterator it = chain.begin(); it != chain.end(); ++it) { temp.InsertFront(*it); }	// ������� ����ϱ����� temp ü�ο� �ٽ� �־��ٰ� ���� ����
	for (CircularListWithHeader<int>::Iterator it = temp.begin(); it != temp.end(); ++it) {
		cout << *it << " ";
	}
	cout << endl;
	// ���� ü�ο��� �ּ� ���� ã�� ��� (ü�� �ݺ��� ���)
	int minValue = 99999;
	for (CircularListWithHeader<int>::Iterator it = chain.begin(); it != chain.end(); ++it)
		if (minValue > *it)	minValue = *it;
	cout << " - �ּ� �� : " << minValue << endl;

	return 0;
}