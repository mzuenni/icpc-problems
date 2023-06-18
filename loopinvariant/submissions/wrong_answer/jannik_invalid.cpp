#include<iostream>
using namespace std;
int main() {
	string s;
	cin >> s;
	int o = 1, l = 1;
	for (; o > 0; l++)
		o += (s[l] == '(' ? 1 : -1);

	auto ns = s.substr(l) + s.substr(0, l);
	if (s==ns)
		cout << "no";
	else
		cout << s.substr(2) << s.substr(0,2);
}
