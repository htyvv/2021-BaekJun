#include<iostream>
#include<algorithm>
#include<sstream>
#include<string>
#include<vector>
#include<cmath>

using namespace std;
typedef long long ll;

ll n;
string input;
vector<vector<string>> ip;
vector<string> binary;

ll nIdx; // 0 ~ 3
ll mIdx; // 0 ~ 7

vector<string> split(string str, char delimeter) {
	vector<string> result;
	stringstream ss(str);
	string token;
	while (getline(ss, token, delimeter)) result.push_back(token);
	return result;
}

ll toDecimal(string binary) {
	ll result = 0;
	for (ll i = 0; i < binary.length(); i++) { 
		result += (binary[i]-'0') * pow(2, binary.length() - 1 - i);
	}
	return result;
}

string toBinary(ll num) {
	string result = "";
	while (num != 0) {
		result += (num % 2 == 0 ? "0" : "1");
		num /= 2;
	}
	reverse(result.begin(), result.end());
	return result;
}

int main() {

	// 입력 받기
	cin >> n;
	for (ll i = 0; i < n; i++) {
		cin >> input;
		ip.push_back(split(input, '.'));
	}


	// nIdx 찾기
	ll idx = 0;
	bool isFin = false;
	while (idx < 4) {
		string curr = ip[0][idx];
		for (ll i = 0; i < n; i++) {
			if (ip[i][idx] != curr) {
				nIdx = idx;
				isFin = true;
			}
		}
		if (isFin) break;
		idx++;
	}


	// nIdx 이후의 수 이진수로 변환
	for (ll i = 0; i < n; i++) {
		string temp = "";
		for (ll j = nIdx; j < 4; j++) temp += ip[i][j];
		binary.push_back(toBinary(stoi(temp)));
	}


	// mIdx 찾기
	idx = 0;
	isFin = false;
	while (true) {
		char curr = binary[0][idx];
		for (ll i = 0; i < n; i++) {
			if (binary[i][idx] != curr) {
				mIdx = idx;
				isFin = true;
			}
		}
		if (isFin) break;
		idx++;
	}

	string nres = "", mres = "";
	string tmp_str = "";
	string bin = toBinary(stoi(ip[0][nIdx]));
	for (ll i = 0; i < mIdx; i++) {
		tmp_str += bin[i];
	}
	// 이후에 0 추가 개수 ( 총 0 개수 - mIdx 앞까지)
	for (ll i = 0; i < ((8 * (4 - nIdx)) - mIdx); i++) tmp_str += "0";

	for (ll i = 0; i < nIdx; i++) {
		nres += ip[0][i];
		nres += ".";
	}

	//cout << "tmp_str : " << tmp_str << endl;
	//cout << "toDecimal(tmp_str) : " << toDecimal(tmp_str) << endl;
	//string temp = to_string(toDecimal(tmp_str));
	//cout << "to_string(toDecimal(tmp_str) : " << temp << endl;

	nres += to_string(toDecimal(tmp_str));

	for (ll i = 0; i < nIdx; i++) mres += "255.";
	string mask = "";
	for (ll i = 0; i < mIdx; i++) mask += "1";
	for (ll i = 0; i < (8-mIdx) + (8*(3-nIdx)); i++) mask += "0";
	mres += to_string(toDecimal(mask));
	
	cout << nres << "\n" << mres;

	return 0;
}