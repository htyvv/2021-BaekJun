#pragma warning(disable : 4996)
#include <iostream>
#include <string>

using namespace std;

template<class T> class CircularListWithHeader;	// 전방 선언

//-------------------------Term----------------------------
struct Term {
	int coef;
	int exp;
	Term(int c = 0, int e = 0.0f) : coef(c), exp(e) {}
	Term Set(int c, int e) { coef = c; exp = e; return *this; }
};

//--------------------------Node---------------------------
template<class T> class TreeNode {
	friend class CircularListWithHeader<T>;
public:
	TreeNode(const T& d) {
		data = d; link = 0;
	}
	~TreeNode() { data.~T(); }
private: 
	T data;
	TreeNode* link;
};
//-----------------CircularListWithHeader-------------------
template<class T>
class CircularListWithHeader {
public:
	class Iterator {	// Iterator 시작
	public:
		//생성자
		Iterator(TreeNode<T>* start) { current = start; }
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
		TreeNode<T>* current;
	};	// Iterator 끝

	// 생성자

	CircularListWithHeader(const T& data) {
		header = new TreeNode<T>(data);
		header->link = header;
		last = header;
	}

	// 체인 조작 연산들
	Iterator begin() { return Iterator(header->link); }	// 리스트의 첫 번째 노드 위치
	Iterator end() { return Iterator(last); }	// 리스트이 맨 마지막 노드를 하나 지난 위치

	inline bool isEmpty() { return header->link == header; }

	void InsertFront(const T& data) {
		TreeNode<T>* newNode = new TreeNode<T>(data);
		last->link = newNode;
		last = newNode;
		last->link = header;
	}

	void popFront() {
		if (!isEmpty()) {
			TreeNode<T>* delNode = header->link;
			header->link = delNode->link;
			delNode->~TreeNode();
			delete delNode;
		}
	}

private:
	TreeNode<T>* header;
	TreeNode<T>* last;
};



//-----------------------Polynomial------------------------
class Polynomial {
private:
	CircularListWithHeader<Term>* poly;
public:
	Polynomial() { poly = new CircularListWithHeader<Term>(Term(0, -1)); }
	Polynomial operator+ (Polynomial& p);
	Polynomial operator* (Polynomial& p);
	friend istream& operator>> (istream& is, Polynomial& p);
	friend ostream& operator<< (ostream& os, Polynomial& p);
	Polynomial sMultPoly(const Term& data);
	int evalPoly(int x);
	void newTerm(const Term& data) { poly->InsertFront(data); }
	bool isEmpty() { return poly->isEmpty(); }

	CircularListWithHeader<Term>::Iterator begin() { return poly->begin(); }
	CircularListWithHeader<Term>::Iterator end() { return poly->end(); }

};

Polynomial Polynomial::operator+(Polynomial& r) {

	CircularListWithHeader<Term>::Iterator left_itr = begin();
	CircularListWithHeader<Term>::Iterator right_itr = r.begin();

	Polynomial result;
	int sum_coef = 0;

	Term left_term = *left_itr;
	Term right_term = *right_itr;
	Term result_term;

	while (left_itr->exp != -1 || right_itr->exp != -1) {
		left_term = *left_itr;
		right_term = *right_itr;
		if (left_term.exp > right_term.exp) {
			result.newTerm(left_term);
			++left_itr;
		}
		else if (left_term.exp < right_term.exp) {
			result.newTerm(right_term);
			++right_itr;
		}
		else {
			sum_coef = left_term.coef + right_term.coef;
			if (sum_coef) {
				result_term.coef = sum_coef;
				result_term.exp = left_term.exp;
				result.newTerm(result_term);
			}
			++left_itr;
			++right_itr;
		}
	}
	return result;
}
Polynomial Polynomial::operator*(Polynomial& p) {
	Polynomial result;
	CircularListWithHeader<Term>::Iterator it = p.begin();
	Term term = *it;
	while (term.exp != -1) {
		Polynomial temp = sMultPoly( Term(term.coef, term.exp) );
		result = result + temp;
		term = *(++it);
	}
	return result;
}

istream& operator>> (istream& is, Polynomial& p) {

	char input_str[4000];
	is >> input_str;

	// 입력 형식 오류에 대한 예외처리를 위한 부분
	int open = 0, close = 0, comma = 0;
	for (int i = 0; i < strlen(input_str); i++) {
		if (input_str[i] == '(') open++;
		else if (input_str[i] == ')') close++;
		else if (input_str[i] == ',') comma++;
	}
	if (open != close || comma != open) {
		std::cout << "\n>Wrong input format. Please try again!\n";
		return is;
	}

	float input_coef[1000];
	int input_exp[1000];

	int input_terms = 0;

	// 괄호와 콤마를 기준으로 tokenize 
	char* token = strtok(input_str, "(,)");

	// # 이 입력되면 종료
	if (strcmp(token, "#") == 0) {
		std::cout << "\n>Exiting program.\n";
		exit(0);
	}

	// 입력받는 coef와 exp순서대로 저장하기
	while (token != NULL) {

		// 토큰을 사용한 Coef 임시 저장
		float next_coef = atof(token);
		if (next_coef == 0 && !(strcmp(token, "0") == 0)) {	// coef에 숫자아닌 문자가 들어올 때 예외처리
			std::cout << "\n>You entered wrong Coefficient. Please try again!\n";
			return is;
		}
		token = strtok(NULL, "(,)");
		// 토큰을 사용한 Exp 임시 저장
		int next_exp = atoi(token);
		float float_exp = atof(token);
		if (next_exp == 0 && !(strcmp(token, "0") == 0)) {	// exp에 숫자아닌 문자가 들어올 때 예외처리
			std::cout << "\n>You entered wrong Exponent. Please try again!\n";
			return is;
		}
		if (next_exp < 0) {	// exp가 음수일 때 예외처리
			std::cout << "\n>Negative Exponent is not allowed. Please try again!\n";
			return is;
		}
		if (float_exp != next_exp) {	// exp가 소수일 때 예외처리
			std::cout << "\n>Decimal Exponent is not allowed. Please try again!\n";
			return is;
		}
		token = strtok(NULL, "(,)");

		input_coef[input_terms] = next_coef;	// 계수 입력 받기
		input_exp[input_terms] = next_exp;	// 지수 입력 받기	

		input_terms++;	// 입력받은 항의 개수 증가
	}

	for (int i = 0; i < input_terms; i++) {
		// 계수가 0이면 없는 항으로 간주
		if (input_coef[i] == 0) {
			continue;
		}
		else {
			Term* temp = new Term(input_coef[i], input_exp[i]);
			p.newTerm(*temp);
		}
	}

	return is;
}
ostream& operator<< (ostream& os, Polynomial& p) {

	// 항이 없는 경우 0을 출력
	if (p.isEmpty()) {
		os << "0";
		return os;
	}

	// 정렬 해야함
	
	CircularListWithHeader<Term>::Iterator curr = p.begin();
	Term term = *curr;
	
	while (term.exp != -1) {
		CircularListWithHeader<Term>::Iterator next = curr; next++;
		Term next_term = *next;
		while (next_term.exp != -1) {

			if (term.exp < next_term.exp) {
				Term temp = term;
				term = next_term;
				next_term = temp;
			}

			next_term = *(++next);
		}
		term = *(++curr);
	}

	// Iterator를 사용한 출력 부분
	curr = p.begin();
	term = *curr;
	bool isFirst = true;
	while (term.exp != -1) {
		
		int curr_coef = curr->coef;
		int curr_exp = curr->exp;

		if (isFirst) {
			isFirst = false;
			if (curr_coef == 0) continue;

			if (curr_exp == 0) {
				if (curr_coef > 0) os << curr_coef;
				else os << curr_coef;
			}

			if (curr_exp == 1) {
				if (curr_coef == 1) os << "x";
				else if (curr_coef == -1) os << "-x";
				else if (curr_coef > 0) os << curr_coef << "x";
				else os << curr_coef << "x";
			}

			if (curr_exp > 1) {
				if (curr_coef == 1) os << "x^" << curr_exp;
				else if (curr_coef == -1) os << "-x^" << curr_exp;
				else if (curr_coef > 0) os << curr_coef << "x^" << curr_exp;
				else os << curr_coef << "x^" << curr_exp;
			}
			++curr;
			term = *curr;
			continue;
		}

		if (curr_coef == 0) {
			++curr;
			term = *curr;
			continue;
		}

		if (curr_exp == 0) {
			if (curr_coef > 0) os << "+" << curr_coef;
			else os << curr_coef;
		}

		if (curr_exp == 1) {
			if (curr_coef == 1) os << "+x";
			else if (curr_coef == -1) os << "-x";
			else if (curr_coef > 0) os << "+" << curr_coef << "x";
			else os << curr_coef << "x";
		}

		if (curr_exp > 1) {
			if (curr_coef == 1) os << "+x^" << curr_exp;
			else if (curr_coef == -1) os << "-x^" << curr_exp;
			else if (curr_coef > 0) os << "+" << curr_coef << "x^" << curr_exp;
			else os << curr_coef << "x^" << curr_exp;
		}

		++curr;
		term = *curr;
	}

	return os;
}

Polynomial Polynomial::sMultPoly(const Term& data) {
	Polynomial result;
	CircularListWithHeader<Term>::Iterator it = begin();
	Term term = *it;
	while (term.exp != -1) {
		result.newTerm( Term(term.coef * data.coef, term.exp + data.exp) );
		term = *(++it);
	}
	return result;
}

int Polynomial::evalPoly(int x) {
	int result = 0;
	CircularListWithHeader<Term>::Iterator it = begin();
	Term term = *it;
	while (term.exp != -1) {
		result += term.coef * pow(x, term.exp);
		term = *(++it);
	}
	return result;
}

int main() {

	while (true) {

		Polynomial a, b, c, d, t;
		int x;

		std::cout << "\n>Input polynomials a, b, c: ";
		std::cin >> a >> b >> c;

		// 예외처리 부분 (입력의 형식이 맞지 않을 때)
		if (a.isEmpty() || b.isEmpty() || c.isEmpty()) {
			continue;
		}

		// '#'이 입력되면 종료되게, operator<< 함수 내부적으로 구현했음

		std::cout << "A(x)= " << a << endl;
		std::cout << "B(x)= " << b << endl;
		std::cout << "C(x)= " << c << endl;
		t = a * b;
		d = t + c;
		std::cout << "T(x)= " << t << endl;
		std::cout << "D(x)= " << d << endl;

		while (true) {
			std::cout << "\n>Input x value: ";
			std::cin >> x;
			// 예외처리 부분 (정수가 아닌 문자를 잘못 입력했을 때)
			if (std::cin.fail()) {
				std::cout << "You entered wrong number. Please try again!" << endl;
				std::cin.clear();
				std::cin.ignore(256, '\n');
				continue;
			}
			break;
		}

		std::cout << "A * B + C = " << d.evalPoly(x) << endl;
	}

	return 0;
}
