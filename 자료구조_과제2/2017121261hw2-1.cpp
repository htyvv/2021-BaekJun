#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
#include<algorithm>

using namespace std;

// 단어 선택정렬 함수
void selection_sort(vector<string> &words) {
	for (int i = 0; i < words.size(); i++) {
		int min_idx = i;
		for (int j = i + 1; j < words.size(); j++) {
			if (words[min_idx] > words[j]) min_idx = j;
		}
		swap(words[min_idx], words[i]);
	}
}

// 단어 이원탐색 함수
int binary_word_search(const vector<string> &words, string word) {

	int left = 0;
	int right = words.size() - 1;
	int mid = 0;

	while (left <= right) {

		mid = (left + right) / 2;

		if (words[mid] == word) 
			return mid + 1;
		else if (words[mid] < word)
			left = mid + 1;
		else 
			right = mid - 1;

	}
	return -1;
	
}

int main() {

	// 프로젝트 폴더 안에 있는 input.txt 읽어오기
	ifstream fin("input.txt");

	// 읽기에 실패하면 프로그램 종료, 성공하면 메뉴로 진입
	if (fin.fail()) {
		cout << "\n[input.txt\"를 불러오는데 실패했습니다. 프로그램을 종료합니다]\n";
		return 0;
	}
	else cout << "\n[input.txt\"를 불러오는데 성공했습니다]\n";

	// txt 파일의 전체 내용을 input 변수에 string 형식으로 저장하기
	string input_raw = "";
	char c;	// 파일 속 한글자 씩 읽기 위한 변수
	while (fin.get(c)) input_raw += c;	// 더 이상 읽을 글자가 없을 때 까지 저장

	// 문장 부호 제거
	string input_processed = "";
	for (int i = 0; i < input_raw.size(); i++) {
		if (input_raw[i] == '\'' || input_raw[i] == '\"' || input_raw[i] == '!' || input_raw[i] == '?' || input_raw[i] == ',' || input_raw[i] == '.') {
			continue;
		}
		input_processed += input_raw[i];
	}

	// 종료 명령을 지시 받기 전까지 모든 메뉴 반복 제공(input.txt 읽기에 성공한 경우)
	while (true) {

		// 메뉴 제공
		string menu_interface = "\n";
		menu_interface += "[원하시는 메뉴를 선택해주세요]\n\n";
		menu_interface += "[1] 요구 기능 수행\n";
		menu_interface += "[2] 종료\n";
		menu_interface += ">>>  ";
		cout << menu_interface; 

		int menu_idx; cin >> menu_idx;

		if (menu_idx == 1) {	

			// 입력파일 내용 확인
			cout << "\n[입력파일 내용 확인]\n";
			cout << input_raw << "\n";
			cout << "\n[문장부호를 제거한 내용 확인]\n";
			cout << input_processed << "\n";

			// stringstream 을 이용한 tokenize로 문장에서 단어들을 vector의 원소로 넘겨줌
			vector<string> words;
			stringstream ss(input_processed);
			string token;
			while (ss >> token) words.push_back(token);

			// 단어들을 선택 정렬 하기
			selection_sort(words);

			// 출력하기
			cout << "\n[정렬된 단어 리스트]";
			for (int i = 1; i <= words.size(); i++) {
				cout << "\n  " << i << ".\t" << words[i-1];
			}
			cout << "\n";

			// 중복 제거
			words.erase(unique(words.begin(), words.end()), words.end());
			cout << "\n[중복 제거된 단어 리스트]";
			for (int i = 1; i <= words.size(); i++) {
				cout << "\n  " << i << ".\t" << words[i - 1];
			}
			cout << "\n";

			// 단어 검색
			while (true) {
				cout << "\n[검색어를 입력해주세요]\n>>>  ";
				string to_find_str; cin >> to_find_str;
				if (to_find_str == ".") {
					cout << "\n[검색을 종료합니다]\n";
					break;
				}
				cout << "검색어 : " << to_find_str << "\t검색 결과(인덱스) : "<< binary_word_search(words, to_find_str) << "\n";
			}
			

		}

		else if (menu_idx == 2) {	// 2. 종료

			cout << "\n[프로그램을 종료합니다]\n";
			fin.close();
			return 0;
			break;

		}
		else {	// 메뉴 번호를 잘못 입력 했을 때

			cout << "\n[메뉴를 잘못 선택하셨습니다. 다시 선택해주세요]\n";

		}

	}

	return 0;
}