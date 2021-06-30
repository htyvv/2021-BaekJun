#pragma warning(disable : 4996)
#include<iostream>
#include<cstring>

using namespace std;

class Polynomial;	// 전방 선언

class Term {	// 항을 정의한 클래스
	friend Polynomial;
	friend istream& operator>> (istream& is, Polynomial& p);
	friend ostream& operator<< (ostream& os, Polynomial& p);
private:
	float coef;
	int exp;
};

class Polynomial {	// 다항식을 정의한 클래스
private:
	Term* termArray;
	int capacity;
	int terms;
public:
	Polynomial();
	Polynomial operator+ (Polynomial& p);
	Polynomial operator* (Polynomial& p);
	friend istream &operator>> (istream& is, Polynomial& p);
	friend ostream &operator<< (ostream& os, Polynomial& p);
	void sortTerms();
	Polynomial addPoly(const Polynomial &p);
	Polynomial multPoly(const Polynomial &p);
	Polynomial sMultPoly(const float theCoeff, const int theExp);
	float evalPoly(const float f);
	void newTerm(const float theCoeff, const int theExp);
	bool isEmpty();
};


// 생성자 : 변수들을 초기화 하면서 메모리 동적 할당
Polynomial::Polynomial() : capacity(1), terms(0) {
	termArray = new Term[capacity];
}


// 더하기, 곱하기, 입출력 연산자 오버로딩
Polynomial Polynomial::operator+ (Polynomial& p) {
	return addPoly(p);
}
Polynomial Polynomial::operator* (Polynomial& p) {
	return multPoly(p);
}

/*
* 입력 스트림을 한 글자식 분석하는 입력 알고리즘
* 이런 방식으로 구현하면 Coex가 소수일 경우 불가능
* 사용자가 완전한(coex, exp) 형식을 지켜줘야함
* 
istream &operator>> (istream& is, Polynomial& p) {
	
	string input;
	bool isCoef = true;
	bool isMinus = false;
	float coef = 0.0f, exp = 0.0f;

	is >> input;

	// 프로그램 종료 조건
	if (input == "#") exit(0);

	for (int i = 0; i < input.length(); i++) {
		if (input[i] == '(') {
			coef = 0.0f;
			isCoef = true;
			continue;
		}			
		if (input[i] == ',') {
			isCoef = false;
			isMinus = false;
			exp = 0.0f;
			continue;
		}
		if (input[i] == ')') {
			p.newTerm(coef, exp);
			continue;
		}
		if (input[i] == '-') {
			isMinus = true;
			continue;
		}

		// 숫자가 아닌 문자 입력됬을때 예외처리
		if (!('0' <= input[i] && input[i] <= '9')) return is;

		if (isCoef) {
			if(isMinus) coef = (coef*10) - (input[i] - '0');
			else coef = (coef * 10) + (input[i] - '0');
		} 
		else exp = (exp*10) + (input[i] - '0');
	}
	return is;
}
*/

// 입력 조건 : 지수와 계수 모두 정수여야하고 음수인 지수는 배제한다.
istream& operator >>(istream& is, Polynomial& p) {

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
			p.newTerm(input_coef[i], input_exp[i]);
		}
	}

	return is;
}

// 첫번째 계수가 양의 정수인 경우 +를 붙이지 않기위해 케이스를 두개로 나눴음
// 
ostream &operator<< (ostream& os, Polynomial& p) {

	// 만약 모든 항의 coef 가 0인 경우 -> 항이 없는 경우 0을 출력
	bool isEmpty = true;
	for (int i = 0; i < p.terms; i++) {
		if (p.termArray[i].coef != 0) {
			isEmpty = false;
			break;
		}
	}
	if (isEmpty) {
		os << "0";
		return os;
	}

	for (int i = 0; i < p.terms; i++) {
		
		float curr_coef = p.termArray[i].coef;
		int curr_exp = p.termArray[i].exp;

		if (i == 0) {
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
			continue;
		}

		if(curr_coef == 0) continue;

		if (p.termArray[i].exp == 0) {
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

	}
	return os;
}

void Polynomial::sortTerms() {
	for (int i = 0; i < terms; i++)
		for (int j = i + 1; j < terms; j++)
			if (termArray[i].exp < termArray[j].exp) {
				Term temp = termArray[i];
				termArray[i] = termArray[j];
				termArray[j] = temp;
			}
}

Polynomial Polynomial::addPoly(const Polynomial &p) {
	Polynomial result;
	int aPos = 0;
	int bPos = 0;
	while (aPos < terms && bPos < p.terms) {
		if (termArray[aPos].exp == p.termArray[bPos].exp) {
			int c_coef = termArray[aPos].coef + p.termArray[bPos].coef;
			if (c_coef != 0) result.newTerm(c_coef, termArray[aPos].exp);
			aPos++; bPos++;
		}
		else if (termArray[aPos].exp > p.termArray[bPos].exp) {
			result.newTerm(termArray[aPos].coef, termArray[aPos].exp);
			aPos++;
		}
		else {
			result.newTerm(p.termArray[bPos].coef, p.termArray[bPos].exp);
			bPos++;
		}
	}
	for(; aPos < terms; aPos++) result.newTerm(termArray[aPos].coef, termArray[aPos].exp);
	for (; bPos < p.terms; bPos++) result.newTerm(p.termArray[bPos].coef, p.termArray[bPos].exp);

	return result;
}

Polynomial Polynomial::sMultPoly(const float theCoeff, const int theExp) {
	Polynomial result;
	for (int i = 0; i < terms; i++) {
		result.newTerm(termArray[i].coef * theCoeff, termArray[i].exp + theExp);
	}
	return result;
}

Polynomial Polynomial::multPoly(const Polynomial &p) {
	Polynomial result;
	for (int i = 0; i < p.terms; i++) {
		result = result.addPoly(sMultPoly(p.termArray[i].coef, p.termArray[i].exp));
	}
	return result;
}

float Polynomial::evalPoly(const float f) {
	float result = 0.0f;
	for (int i = 0; i < terms; i++) result += termArray[i].coef * pow(f, termArray[i].exp);
	return result;
}

void Polynomial::newTerm(const float theCoeff, const int theExp) {
	// 메모리 공간 할당에 관한 부분
	if (terms == capacity) {
		capacity *= 2;
		Term* temp = new Term[capacity];
		copy(termArray, termArray + terms, temp);
		delete[] termArray;
		termArray = temp;
	}

	// 동일한 차수의 항이 있는지 검사
	for (int i = 0; i < terms; i++) {
		// 있으면 계수끼리만 더 해줌
		if (termArray[i].exp == theExp) {
			termArray[i].coef += theCoeff;
			return;
		}
	}

	// 동일한 차수의 항이 없으면 새로운 항을 추가
	termArray[terms].coef = theCoeff;
	termArray[terms++].exp = theExp;

	// 내림차순 정렬
	sortTerms();

}

bool Polynomial::isEmpty() {
	if (terms == 0) return true;
	else return false;
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
	
	/*
	--------------------------
	---------[Debug]----------
	--------------------------

	Polynomial a;
	cin >> a;
	cout << a;

	--------------------------
	--------------------------
	-------------------------- 
	 */ 
	
	return 0;

}