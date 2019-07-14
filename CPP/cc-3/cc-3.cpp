// cc-3.cpp : Defines the entry point for the console application.
//

#include <cstdint>
#include <iostream>
using namespace std;

int64_t bits[32];

uint64_t get_sumbits(uint32_t val) {

	uint64_t sum = 0;
	int i = 31;

	uint16_t ps = 0;
	for (; i >= 0; i--)
		if (val & (1 << i)) {
		sum += bits[i];
		sum += (1 << i) * ps++;
		}

	return sum;
}

int main(int argc, char* argv[])
{

	uint64_t sumb2 = 0;

	int j = 0;
	for (j = 0; j <  31; j++) {

		sumb2 = sumb2 * 2 + uint64_t(1 << j);
		bits[j + 1] = sumb2 + 1;

		if (j == 0)
			bits[j] = sumb2;
	}
	
	
	int n = 0;
	int a = 0;
	int b = 0;

	cin >> n;

	while (n--) {
		cin >> a;
		cin >> b;

		uint64_t sumb = 0;

		
		if ((a < 0 && b < 0) || (a >= 0 && b >= 0))
			sumb = get_sumbits(b) - get_sumbits(a ? a - 1 : 0);

		else if (a < 0 && b >= 0) {
			sumb += get_sumbits(-1) - get_sumbits(a - 1);
			sumb += get_sumbits(b);
		}

		cout << sumb << endl;
	}

	return 0;
}

