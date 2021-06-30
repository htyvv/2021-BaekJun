#include <iostream>
#include <cstring>

using namespace std;

int main() {

	string king; cin >> king;
	string stone; cin >> stone;
	int n; cin >> n;

	char kng_col = king[0];
	char stn_col = stone[0];
	int kng_row = king[1] - '0';
	int stn_row = stone[1] - '0';

	while (n--) {

		string next; cin >> next;

		// R, L, B, T
		if (next.size() == 1) {
			switch (next[0]) {
			case 'R':
				// ŷ �����ʿ� ���� �پ��ְ�
				if (kng_col + 1 == stn_col && kng_row == stn_row) {
					// ���� ���� �о����� ����� ������ ������ ������
					if (stn_col != 'H') {
						// �Ѵ� ���������� �� ĭ��
						kng_col += 1;
						stn_col += 1;
					}
				}
				// ŷ�� ���κ��� �������̸鼭 
				// ŷ�� �о����� ����� ������ ������ ������
				else if (kng_col != 'H') {
					// ŷ�� ���������� �� ĭ
					kng_col += 1;
				}
				break;
			case 'L':
				if (kng_col - 1 == stn_col && kng_row == stn_row) {
					if (stn_col != 'A') {
						kng_col -= 1;
						stn_col -= 1;
					}
				}
				else if (kng_col != 'A') {
					kng_col -= 1;
				}
				break;
			case 'B':
				if (kng_row - 1 == stn_row && kng_col == stn_col) {
					if (stn_row != 1) {
						kng_row -= 1;
						stn_row -= 1;
					}
				}
				else if (kng_row != 1) {
					kng_row -= 1;
				}
				break;
			case 'T':
				if (kng_row + 1 == stn_row && kng_col == stn_col) {
					if (stn_row != 8) {
						kng_row += 1;
						stn_row += 1;
					}
				}
				else if (kng_row != 8) {
					kng_row += 1;
				}
				break;
			}
		}
		// RT, LT, RB, LB
		else {
			switch (next[0] + next[1]) {
			case ('R' + 'T'):
				if (kng_col + 1 == stn_col && kng_row + 1 == stn_row) {
					if (stn_col != 'H' && stn_row != 8) {
						kng_col += 1;
						stn_col += 1;
						kng_row += 1;
						stn_row += 1;
					}
				}
				else if (kng_col != 'H' && kng_row != 8) {
					kng_col += 1;
					kng_row += 1;
				}
				break;
			case ('L' + 'T'):
				if (kng_col - 1 == stn_col && kng_row + 1 == stn_row) {
					if (stn_col != 'A' && stn_row != 8) {
						kng_col -= 1;
						stn_col -= 1;
						kng_row += 1;
						stn_row += 1;
					}
				}
				else if (kng_col != 'A' && kng_row != 8) {
					kng_col -= 1;
					kng_row += 1;
				}
				break;
			case ('R' + 'B'):
				if (kng_col + 1 == stn_col && kng_row - 1 == stn_row) {
					if (stn_col != 'H' && stn_row != 1) {
						kng_col += 1;
						stn_col += 1;
						kng_row -= 1;
						stn_row -= 1;
					}
				}
				else if (kng_col != 'H' && kng_row != 1) {
					kng_col += 1;
					kng_row -= 1;
				}
				break;
			case ('L' + 'B'):
				if (kng_col - 1 == stn_col && kng_row - 1 == stn_row) {
					if (stn_col != 'A' && stn_row != 1) {
						kng_col -= 1;
						stn_col -= 1;
						kng_row -= 1;
						stn_row -= 1;
					}
				}
				else if (kng_col != 'A' && kng_row != 1) {
					kng_col -= 1;
					kng_row -= 1;
				}
				break;

			}

		}
	}

	cout <<  kng_col << kng_row << "\n";
	cout <<  stn_col << stn_row << "\n";

}