#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<ctime>

using namespace std;

class Date {
private :
	int year;
	int month;
	int day;
public:
	Date() {}
	Date(int y, int m, int d);
	void setDate(string info);
	bool isValid();
	int get_year() { return year; }
	int get_month() { return month; }
	int get_day() { return day; }
};

Date::Date(int y, int m, int d) {
	year = y;
	month = m;
	day = d;
}

void Date::setDate(string info) {

	// [����], [��], [��]�� parsing
	stringstream ss(info);
	string token;
	vector<string> tokens;
	while (getline(ss, token, '/')) {
		tokens.push_back(token);
	}

	// ������ ���� ��������� ����
	year = stoi(tokens[0]);
	month = stoi(tokens[1]);
	day = stoi(tokens[2]);

	// ��ȿ�� Date���� �˻� �� -> �߸��� Date�̸� �����޽��� ��� �� ���� 
	if (!isValid()) {
		cout << "��ȿ���� ���� Date�Դϴ�.";
		exit(1);
	}

}

// ����� Date�� �޷»����� ��ȿ���� �Ǻ��ϴ� �Լ�
bool Date::isValid() {
	if (month < 1 || month > 12) return false;
	switch (month) {
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		if (day < 1 || day > 31) return false;
		break;
	case 4: case 6: case 9: case 11:
		if (day < 1 || day > 30) return false;
		break;
	case 2:
		// 4�� �ֱ��� ���� ��� -> ex) 2016, 2020, 2024���� 2���� 29�ϱ��� ����
		if (year % 4 == 0) {
			if (day < 1 || day > 29) return false;
			break;
		}
		else {
			if (day < 1 || day > 28) return false;
			break;
		}
	}
	return true;
}


class Student {
private :
	string major;
	string name;
	string code;
	string birth;
	int age;
public:
	void input();
	void calculate_age();
	void print_info();
};

void Student::input() {

	cout << "ȯ���մϴ�! �а���, �й�, �̸�, �������(yyyy/mm/dd)�� �Է��ϼ���> ";

	// ��ü ���� �Է� �ޱ�
	string input_info; 
	getline(cin, input_info);

	// ��ü ���� -> ������ ������ parsing
	stringstream ss(input_info); 
	string token;
	vector<string> tokens;
	bool isFirst = true;
	while (getline(ss, token, ',')) {
		if (isFirst) {
			isFirst = false;
			tokens.push_back(token);
			continue;
		}
		token.erase(0, 1);	// ',' �������� parsing �Ŀ� �տ� ���� �����̽� ��ĭ ����
		tokens.push_back(token);
	}

	// ������ ���� ��������� ����
	major = tokens[0];
	code = tokens[1];
	name = tokens[2];
	birth = tokens[3];

}

void Student::calculate_age() {
	
	// ���û��� ���� �ð��� �ҷ���
	time_t curr_time = time(nullptr);
	struct tm *curr_tm = localtime(&curr_time);
	Date today(curr_tm->tm_year + 1900, curr_tm->tm_mon + 1, curr_tm->tm_mday);

	// �л��� ������ �ҷ���
	Date birthday;
	birthday.setDate(birth);
	
	// �� ���� ���
	age = today.get_year() - birthday.get_year();
	if (today.get_month() < birthday.get_month()) {
		age--;
	}
	else if (today.get_month() == birthday.get_month()) {
		if ((today.get_day() < birthday.get_day()))
			age--;
	}

}

void Student::print_info() {

	// ���û��� ���� �ð��� �ҷ���
	time_t curr_time = time(nullptr);
	struct tm* curr_tm = localtime(&curr_time);
	Date today(curr_tm->tm_year + 1900, curr_tm->tm_mon + 1, curr_tm->tm_mday);

	// �л��� ������ �ҷ���
	Date birthday;
	birthday.setDate(birth);

	// ���
	cout << ">> " << major << " " << code << " " << name << "��" << " " << birthday.get_year() << "��" << birthday.get_month() << "��" << birthday.get_day() << "�ϻ� "
		<< today.get_year() << "��" << today.get_month() << "��" << today.get_day() << "�� ���� " << age << "���Դϴ�.";

}

int main() {
	
	Student student;
	student.input();
	student.calculate_age();
	student.print_info();

}