#include <iostream>
#include <vector>
using namespace std;

vector<int> daily;
int N, M, total;

bool cal(int m)
{
	int temp = m, cnt = 1;
	for (int i = 0; i < N; i++)
	{
		if (daily[i] > m)
			return false;
		if (temp - daily[i] < 0)
		{
			temp = m;
			cnt++;
		}
		temp -= daily[i];
	}
	return M >= cnt;
}
int main(void)
{
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		int n;
		cin >> n;
		daily.push_back(n);
		total += n;
	}

	int left = 1;
	int right = total;
	int result = 0;
	while (left <= right) {
		int mid = (left + right) / 2;
		if (cal(mid))	
		{
			result = mid;
			right = mid - 1;
		}
		else
			left = mid + 1;
	}

	cout << result;

}