#include <iostream>

using namespace std;

class belt {
public:
	bool isRobot = false;
	int durability = 0;
};

int n, k;
belt belts[201];

int main() {

	cin >> n >> k;
	for(int i = 1; i <= 2*n; i++){
		cin >> belts[i].durability;
	}

	// ��Ʈ�� ȸ���� �� ���� cnt++
	// �������� = �������� 0�� ĭ ���� k���� ����

	// 1. ��Ʈ�� ȸ�� ����
	// 2. �� �ܰ� ���� ��Ʈ���� �κ� ������ �̵� Ȯ��(Ư�� ������ �κ� ����)
	// 3. �κ��� �ø��� ���� ����

	int cnt = 0;

	while (1) {

		// ��������
		int zero_belt = 0;
		for (int i = 1; i <= 2 * n; i++) {
			if (belts[i].durability == 0) zero_belt++;
		}
		if (zero_belt >= k) {
			cout << cnt;
			return 0;
		}

		// ��Ʈ�� ȸ��
		belt temp = belts[2 * n];
		belt temp1;
		for (int i = 1; i <= 2 * n; i++) {
			// �� ��Ʈ�� ���� ĭ���� (�������� �κ��� ���� ������)
			belt temp2 = belts[i];
			belts[i] = temp1;
			temp1 = temp2;
		}
		belts[1] = temp;

		// n��° ĭ�� �κ��� �־��ٸ� ������.
		if (belts[n].isRobot == true) {
			belts[n].isRobot = false;
		}

		// �κ����� �̵� Ȯ�� (���� �ö�� �κ� ����)
		for (int i = n-1; i > 0; i--) {
			if (belts[i].isRobot == true) {
				if (belts[i + 1].durability > 0 && belts[i + 1].isRobot == false) {
					belts[i].isRobot = false;
					belts[i + 1].isRobot = true;
					belts[i + 1].durability -= 1;
				}
			}
		}

		// n��° ĭ�� �κ��� �־��ٸ� ������.
		if (belts[n].isRobot == true) {
			belts[n].isRobot = false;
		}

		// �κ��� �̵� �Ŀ� ù��° ĭ�� ������� �� �κ��� �ø���.
		if (belts[1].durability > 0 && belts[1].isRobot == false) {
			belts[1].isRobot = true;
			belts[1].durability -= 1;
		}

		cnt++;

	}
	

	//

	cout << cnt;

}