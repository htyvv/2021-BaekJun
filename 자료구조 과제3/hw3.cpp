#pragma warning(disable : 4996)
#include<iostream>
#include<cstring>

using namespace std;

class Polynomial;	// ���� ����

class Term {	// ���� ������ Ŭ����
	friend Polynomial;
	friend istream& operator>> (istream& is, Polynomial& p);
	friend ostream& operator<< (ostream& os, Polynomial& p);
private:
	float coef;
	int exp;
};

class Polynomial {	// ���׽��� ������ Ŭ����
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


// ������ : �������� �ʱ�ȭ �ϸ鼭 �޸� ���� �Ҵ�
Polynomial::Polynomial() : capacity(1), terms(0) {
	termArray = new Term[capacity];
}


// ���ϱ�, ���ϱ�, ����� ������ �����ε�
Polynomial Polynomial::operator+ (Polynomial& p) {
	return addPoly(p);
}
Polynomial Polynomial::operator* (Polynomial& p) {
	return multPoly(p);
}

/*
* �Է� ��Ʈ���� �� ���ڽ� �м��ϴ� �Է� �˰���
* �̷� ������� �����ϸ� Coex�� �Ҽ��� ��� �Ұ���
* ����ڰ� ������(coex, exp) ������ ���������
* 
istream &operator>> (istream& is, Polynomial& p) {
	
	string input;
	bool isCoef = true;
	bool isMinus = false;
	float coef = 0.0f, exp = 0.0f;

	is >> input;

	// ���α׷� ���� ����
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

		// ���ڰ� �ƴ� ���� �Է����� ����ó��
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

// �Է� ���� : ������ ��� ��� ���������ϰ� ������ ������ �����Ѵ�.
istream& operator >>(istream& is, Polynomial& p) {

	char input_str[4000];
	is >> input_str;

	// �Է� ���� ������ ���� ����ó���� ���� �κ�
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

	// ��ȣ�� �޸��� �������� tokenize 
	char* token = strtok(input_str, "(,)");

	// # �� �ԷµǸ� ����
	if (strcmp(token, "#") == 0) {
		std::cout << "\n>Exiting program.\n";
		exit(0);
	}

	// �Է¹޴� coef�� exp������� �����ϱ�
	while (token != NULL) { 

		// ��ū�� ����� Coef �ӽ� ����
		float next_coef = atof(token);
		if (next_coef == 0 && !(strcmp(token, "0") == 0)) {	// coef�� ���ھƴ� ���ڰ� ���� �� ����ó��
			std::cout << "\n>You entered wrong Coefficient. Please try again!\n";
			return is;
		}
		token = strtok(NULL, "(,)");
		// ��ū�� ����� Exp �ӽ� ����
		int next_exp = atoi(token);
		float float_exp = atof(token);
		if (next_exp == 0 && !(strcmp(token, "0") == 0)) {	// exp�� ���ھƴ� ���ڰ� ���� �� ����ó��
			std::cout << "\n>You entered wrong Exponent. Please try again!\n";
			return is; 
		}
		if (next_exp < 0) {	// exp�� ������ �� ����ó��
			std::cout << "\n>Negative Exponent is not allowed. Please try again!\n";
			return is; 
		} 
		if (float_exp != next_exp) {	// exp�� �Ҽ��� �� ����ó��
			std::cout << "\n>Decimal Exponent is not allowed. Please try again!\n";
			return is;
		}
		token = strtok(NULL, "(,)");
		
		input_coef[input_terms] = next_coef;	// ��� �Է� �ޱ�
		input_exp[input_terms] = next_exp;	// ���� �Է� �ޱ�	

		input_terms++;	// �Է¹��� ���� ���� ����
	}

	for (int i = 0; i < input_terms; i++) {
		// ����� 0�̸� ���� ������ ����
		if (input_coef[i] == 0) {
			continue;
		}
		else {
			p.newTerm(input_coef[i], input_exp[i]);
		}
	}

	return is;
}

// ù��° ����� ���� ������ ��� +�� ������ �ʱ����� ���̽��� �ΰ��� ������
// 
ostream &operator<< (ostream& os, Polynomial& p) {

	// ���� ��� ���� coef �� 0�� ��� -> ���� ���� ��� 0�� ���
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
	// �޸� ���� �Ҵ翡 ���� �κ�
	if (terms == capacity) {
		capacity *= 2;
		Term* temp = new Term[capacity];
		copy(termArray, termArray + terms, temp);
		delete[] termArray;
		termArray = temp;
	}

	// ������ ������ ���� �ִ��� �˻�
	for (int i = 0; i < terms; i++) {
		// ������ ��������� �� ����
		if (termArray[i].exp == theExp) {
			termArray[i].coef += theCoeff;
			return;
		}
	}

	// ������ ������ ���� ������ ���ο� ���� �߰�
	termArray[terms].coef = theCoeff;
	termArray[terms++].exp = theExp;

	// �������� ����
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

		// ����ó�� �κ� (�Է��� ������ ���� ���� ��)
		if (a.isEmpty() || b.isEmpty() || c.isEmpty()) {
			continue;
		}

		// '#'�� �ԷµǸ� ����ǰ�, operator<< �Լ� ���������� ��������
	
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
			// ����ó�� �κ� (������ �ƴ� ���ڸ� �߸� �Է����� ��)
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