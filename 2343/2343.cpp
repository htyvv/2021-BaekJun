#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

vector<int>v;
int n, m;

bool calc(int x)
{
    int cnt = 1;
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        if (v[i] > x) return false;
        sum += v[i];
        if (sum > x) {
            sum = v[i];
            cnt++;
        }
    }
    if (cnt <= m) return true;
    else return false;
}
int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);

    cin >> n >> m;
    v.resize(n);
    for (int i = 0; i < n; i++) cin >> v[i];

    int left = 1, right = 10000 * n;
    int ans = 0;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (calc(mid)) {
            ans = mid;
            right = mid - 1;
        }
        else left = mid + 1;
    }

    cout << ans;

    return 0;
}