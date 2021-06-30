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

	// [연도], [달], [일]로 parsing
	stringstream ss(info);
	string token;
	vector<string> tokens;
	while (getline(ss, token, '/')) {
		tokens.push_back(token);
	}

	// 각각의 정보 멤버변수에 저장
	year = stoi(tokens[0]);
	month = stoi(tokens[1]);
	day = stoi(tokens[2]);

	// 유효한 Date인지 검사 후 -> 잘못된 Date이면 오류메시지 출력 및 종료 
	if (!isValid()) {
		cout << "유효하지 않은 Date입니다.";
		exit(1);
	}

}

// 저장된 Date가 달력상으로 유효한지 판별하는 함수
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
		// 4년 주기의 윤년 고려 -> ex) 2016, 2020, 2024년의 2월은 29일까지 있음
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

	cout << "환영합니다! 학과명, 학번, 이름, 생년월일(yyyy/mm/dd)을 입력하세요> ";

	// 전체 정보 입력 받기
	string input_info; 
	getline(cin, input_info);

	// 전체 정보 -> 각각의 정보로 parsing
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
		token.erase(0, 1);	// ',' 기준으로 parsing 후에 앞에 남은 스페이스 한칸 삭제
		tokens.push_back(token);
	}

	// 각각의 정보 멤버변수에 저장
	major = tokens[0];
	code = tokens[1];
	name = tokens[2];
	birth = tokens[3];

}

void Student::calculate_age() {
	
	// 로컬상의 현재 시간을 불러옴
	time_t curr_time = time(nullptr);
	struct tm *curr_tm = localtime(&curr_time);
	Date today(curr_tm->tm_year + 1900, curr_tm->tm_mon + 1, curr_tm->tm_mday);

	// 학생의 생일을 불러옴
	Date birthday;
	birthday.setDate(birth);
	
	// 만 나이 계산
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

	// 로컬상의 현재 시간을 불러옴
	time_t curr_time = time(nullptr);
	struct tm* curr_tm = localtime(&curr_time);
	Date today(curr_tm->tm_year + 1900, curr_tm->tm_mon + 1, curr_tm->tm_mday);

	// 학생의 생일을 불러옴
	Date birthday;
	birthday.setDate(birth);

	// 출력
	cout << ">> " << major << " " << code << " " << name << "님" << " " << birthday.get_year() << "년" << birthday.get_month() << "월" << birthday.get_day() << "일생 "
		<< today.get_year() << "년" << today.get_month() << "월" << today.get_day() << "일 현재 " << age << "세입니다.";

}

int main() {
	
	Student student;
	student.input();
	student.calculate_age();
	student.print_info();

}