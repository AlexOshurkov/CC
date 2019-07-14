#include "precomp.hpp"

using namespace std;

template<typename T>
vector<T> TestStream() {
	
	ifstream inpf("c:\\data1.txt");
	
	istreambuf_iterator<T> beg1(inpf);
	istreambuf_iterator<T> end1;
	return vector<T> {beg1, end1 };
}

void TestMs() {

}

int verscomp(string v1, string v2) {

	regex rg("\\.");
	
	sregex_token_iterator it1(v1.begin(), v1.end(), rg, -1);
	vector<string> vec1(it1, sregex_token_iterator());
	sregex_token_iterator it2(v2.begin(), v2.end(), rg, -1);
	vector<string> vec2(it2, sregex_token_iterator());

	size_t size1 = vec1.size();
	size_t size2 = vec2.size();

	if (size1 > size2)
		vec2.insert(vec2.end(), size1 - size2, "0");

	else if (size1 < size2)
		vec1.insert(vec1.end(), size2 - size1, "0");

	int res = 0;

	vector<string>::const_iterator cit1 = vec1.begin();
	vector<string>::const_iterator cit2 = vec2.begin();

	while (cit1 != vec1.end())
	{
		int n1 = std::atoi(cit1->c_str());
		int n2 = std::atoi(cit2->c_str());
		++cit1;
		++cit2;		

		if (n1 == n2)
			continue;

		else if (n1 > n2)
			return 1;

		else
			return -1;
	}

	return res;		
}

int divv(int a, int b) {
	
	if (b == 0)
		throw std::exception("Divivde by zero");
	
	int res = 0;
	int sign = (a > 0 && b > 0) || (a < 0 && b < 0) ? 1 : -1;
	a = abs(a);
	b = abs(b);

	while (a >= b) {
		a -= b;
		++res;
	}

	return res * sign;
}

int CompareVersions(string v1, string v2) 
{
	int res = 0;

	string::const_iterator cit1 = v1.begin();
	string::const_iterator cit2 = v2.begin();

	unsigned int n1 = 0;
	unsigned int n2 = 0;

	while (true) 
	{
		if (cit1 == v1.end() && cit2 == v2.end())
			break;

		while (cit1 != v1.end())
		{
			const char ch = *cit1;
			++cit1;

			if (ch == '.')
				break;
			else
			{
				n1 *= 10;
				n1 += ch - '0';
			}
		}

		while (cit2 != v2.end())
		{
			const char ch = *cit2;
			++cit2;

			if (ch == '.')
				break;
			else
			{
				n2 *= 10;
				n2 += ch - '0';
			}
		}

		if (n1 > n2)
			return 1;
		else if (n1 < n2)
			return -1;

		n1 = 0;
		n2 = 0;
	}

	return res;
}


bool TestVersions() 
{
	
	return CompareVersions("1.2.3.4", "1.2.3.4") == 0 &&
		CompareVersions("1.2.3.5", "1.2.3.4") == 1 &&
		CompareVersions("1.2.3.4", "1.2.3.5") == -1 &&
		CompareVersions("", "") == 0 &&
		CompareVersions("1.2.3.4", "1.2.3.4.0.0.0") == 0 &&
		CompareVersions("1.2.3.4", "1.2.3.4.0.0.1") == -1 &&
		CompareVersions("1.2.3.4.0", "1.2.3.4") == 0 &&
		CompareVersions("1.2.3.4.1", "1.2.3.4") == 1 &&
		CompareVersions("1", "") == 1 && 
		CompareVersions("", "1") == -1 &&
		CompareVersions("1", "0") == 1 && 
		CompareVersions("0", "1") == -1 &&
		CompareVersions("11.1", "11.1") == 0;
}

bool is_pal(const string& s, size_t n, size_t size)
{
	if (s.empty())
		return true;

	string::const_iterator it1 = s.begin();  
	string::const_iterator it2 = --s.end();   

	while (it1 < it2)
	{
		if (*it1 != *it2)
			return false;
		++it1;
		--it2;
	}
	return true;
}
//  0. ewq456
// 12
// 123qwewqabc => "abc"
//  1. 123qwewq456
//  2. 123qwewq45, 23qwewq456
//  3. 123qwewq4, 23qwewq45, 3qwewq456
//  ...
//  suffix tree

//1. O(n ^ 3)
//2.


int main4()
{
	
	
	int i1 = divv(25, 5);
	int i2 = divv(-25, 5);
	int i3 = divv(25, -5);
	int i4 = divv(-25, -5);
	int i5 = divv(3, 5);
	int i6 = divv(5, 3);
	int i7 = divv(5, 1);
	int i8 = divv(0, 5);
	int i9 = divv(5, 0);

	bool b = TestVersions();

	return 0;
}
