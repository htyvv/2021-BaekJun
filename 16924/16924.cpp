#include <iostream>
#include <queue>
#include <vector>
#include <tuple>

using namespace std;

#define STAR 1
int N = 0, M = 0;
int input_arr[101][101];
int res_arr[101][101];
int dx[] = { -1,0,1,0 };
int dy[] = { 0,1,0,-1 };

int check_cross(int x, int y)
{
	int dot_sizes[] = { 0,0,0,0 };
	int cross_size = 100;
	for (int i = 0; i < 4; i++)
	{
		int xn = x;
		int yn = y;
		int dot_size = 0;

		while (true)
		{
			xn += dx[i];
			yn += dy[i];
			if (xn < 0 || xn >= M || yn < 0 || yn >= N)	break;
			if (input_arr[yn][xn] == STAR)
				dot_sizes[i] = ++dot_size;
			else
				break;

		}
	}
	for (int i = 0; i < 4; i++)
	{
		if (cross_size >= dot_sizes[i])
			cross_size = dot_sizes[i];
	}
	return cross_size;
}
int main(void)
{
	queue<pair<int, int>> q;
	vector<tuple<int, int, int>> res_v;
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			char tmp_input = 0;
			cin >> tmp_input;
			if (tmp_input == '*')
			{
				input_arr[i][j] = STAR;
				q.push(make_pair(i, j));
			}
		}
	}

	while (!q.empty())
	{
		int cur_star_x = q.front().second;
		int cur_star_y = q.front().first;
		int cross_size = check_cross(cur_star_x, cur_star_y);

		q.pop();
		if (cross_size > 0)
			res_v.push_back(make_tuple(cur_star_y, cur_star_x, cross_size));
	}

	bool is_same = true;

	if (!res_v.empty())
	{
		int cross_num = res_v.size();

		for (int i = 0; i < cross_num; i++)
		{
			int cross_y = get<0>(res_v[i]);
			int cross_x = get<1>(res_v[i]);
			int cross_length = get<2>(res_v[i]);

			res_arr[cross_y][cross_x] = STAR;

			for (int j = 0; j < 4; j++)
			{
				int cross_xn = cross_x;
				int cross_yn = cross_y;

				for (int k = 0; k < cross_length; k++)
				{
					cross_xn += dx[j];
					cross_yn += dy[j];

					res_arr[cross_yn][cross_xn] = STAR;
				}
			}
		}

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				if (input_arr[i][j] != res_arr[i][j])
					is_same = false;
			}
		}

		if (is_same)
		{
			cout << cross_num << endl;

			for (int i = 0; i < cross_num; i++)
			{
				cout << get<0>(res_v[i]) + 1 << " ";
				cout << get<1>(res_v[i]) + 1 << " ";
				cout << get<2>(res_v[i]) << endl;

			}
		}
		else
			cout << -1 << endl;

	}
	else
		cout << -1 << endl;

	return 0;
}