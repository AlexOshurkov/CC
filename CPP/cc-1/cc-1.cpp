#include <iostream>

using namespace std;

int maxXor(int l, int r) {

	for (int b = 31; b >= 0; b--) 
		if (((1 << b) & l) ^ ((1 << b) & r))
			return (1 << b + 1) - 1;

	return 0;
}

int main() {
	int res;
	int _l;
	cin >> _l;

	int _r;
	cin >> _r;

	res = maxXor(_l, _r);
	cout << res;

	return 0;
}