#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
#include<algorithm>

using namespace std;

// �ܾ� �������� �Լ�
void selection_sort(vector<string> &words) {
	for (int i = 0; i < words.size(); i++) {
		int min_idx = i;
		for (int j = i + 1; j < words.size(); j++) {
			if (words[min_idx] > words[j]) min_idx = j;
		}
		swap(words[min_idx], words[i]);
	}
}

// �ܾ� �̿�Ž�� �Լ�
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

	// ������Ʈ ���� �ȿ� �ִ� input.txt �о����
	ifstream fin("input.txt");

	// �б⿡ �����ϸ� ���α׷� ����, �����ϸ� �޴��� ����
	if (fin.fail()) {
		cout << "\n[input.txt\"�� �ҷ����µ� �����߽��ϴ�. ���α׷��� �����մϴ�]\n";
		return 0;
	}
	else cout << "\n[input.txt\"�� �ҷ����µ� �����߽��ϴ�]\n";

	// txt ������ ��ü ������ input ������ string �������� �����ϱ�
	string input_raw = "";
	char c;	// ���� �� �ѱ��� �� �б� ���� ����
	while (fin.get(c)) input_raw += c;	// �� �̻� ���� ���ڰ� ���� �� ���� ����

	// ���� ��ȣ ����
	string input_processed = "";
	for (int i = 0; i < input_raw.size(); i++) {
		if (input_raw[i] == '\'' || input_raw[i] == '\"' || input_raw[i] == '!' || input_raw[i] == '?' || input_raw[i] == ',' || input_raw[i] == '.') {
			continue;
		}
		input_processed += input_raw[i];
	}

	// ���� ����� ���� �ޱ� ������ ��� �޴� �ݺ� ����(input.txt �б⿡ ������ ���)
	while (true) {

		// �޴� ����
		string menu_interface = "\n";
		menu_interface += "[���Ͻô� �޴��� �������ּ���]\n\n";
		menu_interface += "[1] �䱸 ��� ����\n";
		menu_interface += "[2] ����\n";
		menu_interface += ">>>  ";
		cout << menu_interface; 

		int menu_idx; cin >> menu_idx;

		if (menu_idx == 1) {	

			// �Է����� ���� Ȯ��
			cout << "\n[�Է����� ���� Ȯ��]\n";
			cout << input_raw << "\n";
			cout << "\n[�����ȣ�� ������ ���� Ȯ��]\n";
			cout << input_processed << "\n";

			// stringstream �� �̿��� tokenize�� ���忡�� �ܾ���� vector�� ���ҷ� �Ѱ���
			vector<string> words;
			stringstream ss(input_processed);
			string token;
			while (ss >> token) words.push_back(token);

			// �ܾ���� ���� ���� �ϱ�
			selection_sort(words);

			// ����ϱ�
			cout << "\n[���ĵ� �ܾ� ����Ʈ]";
			for (int i = 1; i <= words.size(); i++) {
				cout << "\n  " << i << ".\t" << words[i-1];
			}
			cout << "\n";

			// �ߺ� ����
			words.erase(unique(words.begin(), words.end()), words.end());
			cout << "\n[�ߺ� ���ŵ� �ܾ� ����Ʈ]";
			for (int i = 1; i <= words.size(); i++) {
				cout << "\n  " << i << ".\t" << words[i - 1];
			}
			cout << "\n";

			// �ܾ� �˻�
			while (true) {
				cout << "\n[�˻�� �Է����ּ���]\n>>>  ";
				string to_find_str; cin >> to_find_str;
				if (to_find_str == ".") {
					cout << "\n[�˻��� �����մϴ�]\n";
					break;
				}
				cout << "�˻��� : " << to_find_str << "\t�˻� ���(�ε���) : "<< binary_word_search(words, to_find_str) << "\n";
			}
			

		}

		else if (menu_idx == 2) {	// 2. ����

			cout << "\n[���α׷��� �����մϴ�]\n";
			fin.close();
			return 0;
			break;

		}
		else {	// �޴� ��ȣ�� �߸� �Է� ���� ��

			cout << "\n[�޴��� �߸� �����ϼ̽��ϴ�. �ٽ� �������ּ���]\n";

		}

	}

	return 0;
}