#include <iostream>
#include <string>

using namespace std;

template<class T> class CircularListWithHeader;	// 전방 선언

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
	// 생성자
	CircularListWithHeader() : first(0) {}
	// 반복자
	class Iterator {
	public:
		//생성자
		Iterator(Node<T>* start) { current = start; }
		// 역참조 연산자
		T& operator*() const { return current->data; }
		T* operator->() const { return &current->data; }
		// 증가
		Iterator& operator++() { current = current->link; return *this; }
		Iterator& operator++(int) {
			Iterator old = *this;
			current = current->link;
			return old;
		}
		// 동등 검사
		bool operator!=(const Iterator right) { return current != right.current; }
		bool operator==(const Iterator right) { return current == right.current; }
	private:
		Node<T>* current;
	};

	// 체인 조작 연산들
	Iterator begin() { return iterator(first); }	// 리스트의 첫 번째 노드 위치
	Iterator end() { return iterator(0); }	// 리스트이 맨 마지막 노드를 하나 지난 위치
	void InsertFront(T& data) { first = new Node<T>(data, first); }
private :
	Node<T>* first;
};



int main() {

	CircularListWithHeader<int> chain;
	CircularListWithHeader<int> temp;

	cout << "\t[프로그램 소개]\n" << "원하는 개수 만큼 정수를 입력합니다.\n더 이상 입력을 원치 않으면 #를 입력합니다.\n입력된 모든 원소를 순서대로 출력하고 최소값을 찾아 출력합니다.\n\n";

	// 정수 리스트 입력 받기 > 체인으로
	while (true) {
		cout << "\n체인에 추가할 정수를 입력해 주세요\n>>> ";
		string input; getline(cin, input);
		if (input == "#") break;
		try {
			int num = stoi(input);
			chain.InsertFront(num);
		}
		catch (exception e) {
			cout << "잘못된 입력입니다. 다시 입력해 주세요" << endl;
			continue;
		}		
	}

	// 정수 체인의 모든 원소를 출력 (체인 반복자 사용)
	cout << "\n - 모든 원소 출력 : ";
	for (CircularListWithHeader<int>::Iterator it = chain.begin(); it != chain.end(); ++it) { temp.InsertFront(*it); }	// 순서대로 출력하기위해 temp 체인에 다시 넣었다가 빼기 위함
	for (CircularListWithHeader<int>::Iterator it = temp.begin(); it != temp.end(); ++it) {
		cout << *it << " ";
	}
	cout << endl;
	// 정수 체인에서 최소 값을 찾아 출력 (체인 반복자 사용)
	int minValue = 99999;
	for (CircularListWithHeader<int>::Iterator it = chain.begin(); it != chain.end(); ++it)
		if (minValue > *it)	minValue = *it;
	cout << " - 최소 값 : " << minValue << endl;

	return 0;
}