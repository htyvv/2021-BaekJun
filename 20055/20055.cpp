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

	// 밸트가 회전할 떄 마다 cnt++
	// 종료조건 = 내구도가 0인 칸 새서 k개면 종료

	// 1. 밸트의 회전 구현
	// 2. 각 단계 마다 벨트위의 로봇 마다의 이동 확인(특히 내리는 로봇 유무)
	// 3. 로봇을 올릴지 말지 여부

	int cnt = 0;

	while (1) {

		// 종료조건
		int zero_belt = 0;
		for (int i = 1; i <= 2 * n; i++) {
			if (belts[i].durability == 0) zero_belt++;
		}
		if (zero_belt >= k) {
			cout << cnt;
			return 0;
		}

		// 밸트의 회전
		belt temp = belts[2 * n];
		belt temp1;
		for (int i = 1; i <= 2 * n; i++) {
			// 각 밸트를 다음 칸으로 (내구성과 로봇이 같이 움직임)
			belt temp2 = belts[i];
			belts[i] = temp1;
			temp1 = temp2;
		}
		belts[1] = temp;

		// n번째 칸에 로봇이 있었다면 내린다.
		if (belts[n].isRobot == true) {
			belts[n].isRobot = false;
		}

		// 로봇들의 이동 확인 (먼저 올라온 로봇 부터)
		for (int i = n-1; i > 0; i--) {
			if (belts[i].isRobot == true) {
				if (belts[i + 1].durability > 0 && belts[i + 1].isRobot == false) {
					belts[i].isRobot = false;
					belts[i + 1].isRobot = true;
					belts[i + 1].durability -= 1;
				}
			}
		}

		// n번째 칸에 로봇이 있었다면 내린다.
		if (belts[n].isRobot == true) {
			belts[n].isRobot = false;
		}

		// 로봇의 이동 후에 첫번째 칸이 비었으면 새 로봇을 올린다.
		if (belts[1].durability > 0 && belts[1].isRobot == false) {
			belts[1].isRobot = true;
			belts[1].durability -= 1;
		}

		cnt++;

	}
	

	//

	cout << cnt;

}