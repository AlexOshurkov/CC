
#include <memory.h>

int main()
{
	const int s = 8;
	int ar[s];
	
	int i = 0;
	for (i = 0; i < s; i++)
		ar[i] = 0;

	ar[0] = 1;
	ar[3] = 1;
	ar[6] = 1;

	int b   = 0;
	int mb  = 0;
	int me  = 0;
	int sum = 0;
	int mx  = 0;
	int co  = 0;

	for (i = 0; i < s; i++) {

		if (ar[i])
			co++;

		if (ar[i] == 0) {
			if (sum == 0)
				b = i;

			sum++;
		}

		else if (sum > 0)
			sum--;
		
		if (sum > mx) {
			mx = sum;
			mb = b;
			me = i;
		}
	}

	delete ar;
	return 0;
}

