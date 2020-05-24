#include "stdafx.h"
#pragma hdrstop

using namespace std;

namespace nm2 {

bool CheckRepeatedSubstr(const string& str, size_t len)
{
	if (str.empty())
		return true;
	
	if (str.size() < len || len == 0)
		return false;

	size_t chk_pos = 0;
	string::const_iterator it = str.begin();

	while (it != str.end())
	{
		if (chk_pos >= len)
			chk_pos = 0;

		if (str[chk_pos] != *it)
			return false;

		++it;
		++chk_pos;
	}

	return chk_pos == len && it == str.end();
}

bool IsBuiltFromSubstr(const string& str)
{
	const size_t size = str.size();

	if (size == 0)
		return true;

	if (size == 1)
		return false;

	size_t substrings = 1;
	size_t subsize = size; 

	while (subsize > 0)
	{
		++substrings;

		if (size % substrings && substrings <= size)
			continue;

		subsize = size / substrings;
		
		if (CheckRepeatedSubstr(str, subsize))
			return true;
	}

	return false;
}

void CheckIsBuiltFromSubstr()
{
	cout << endl << (IsBuiltFromSubstr("") == true);
	cout << endl << (IsBuiltFromSubstr("a") == false);
	cout << endl << (IsBuiltFromSubstr("aa") == true);
	cout << endl << (IsBuiltFromSubstr("abab") == true);
	cout << endl << (IsBuiltFromSubstr("abc") == false);
	cout << endl << (IsBuiltFromSubstr("abcafcabc") == false);
	cout << endl << (IsBuiltFromSubstr("abcabcabc") == true);
	cout << endl << (IsBuiltFromSubstr("abcabcabca") == false);
	cout << endl << (IsBuiltFromSubstr("kj2r49JI888hjuiilwWkjKbjCFkj2r49JI888hjuiilwWkjKbjCF") == true);
	cout << endl << (IsBuiltFromSubstr("kj2r49JI888hjuiilwWkjKbjCFkj2r49JI88hjuiilwWkjKbjCF") == false);
	cout << endl << (IsBuiltFromSubstr("abcbaabcbaabcbaabcbaabcbaabcbaabcbaabcbaabcbaabcbaabcbaabcbaabcbaabcbaabcbaabcbaabcbaabcbaabcbaabcbaabcbaabcbaabcbaabcbaabcbaabcbaabcbaabcbaabcbaabcbaabcbaabcbaabcba") == true);
	cout << endl << (IsBuiltFromSubstr("abcbaabcbaabcbaabcbaabcbaabcbaabcbaabcbaabcbaabcbaabcbaabcbaabcbaabcbaabcbaabcbaabcbaabcbaabcbaabcbaabcbaa bcbaabcbaabcbaabcbaabcbaabcbaabcbaabcbaabcbaabcbaabcbaabcba") == false);
}

struct AlignTest
{
	short v2;
	double v1;
	char v3;
	char v4;
	char v5;


};

class MyBase
{
	int i[4];
	virtual void func1() {}
	virtual void func2() {}
	virtual void func3() {}
};

class MyBase1 : MyBase
{
};

class MyBase2 : MyBase
{
};

class MyBase3 : MyBase
{
};

class MyBase4 : MyBase1, MyBase2, MyBase3
{

};

void TestAlign()
{
	std::cout << "\n sizeof (void*): " << sizeof(void*);
	std::cout << "\n sizeof AlignTest: " << sizeof(AlignTest);
	std::cout << "\n sizeof MyBase: " << sizeof(MyBase);
	std::cout << "\n sizeof MyBase4: " << sizeof(MyBase4);
}



void TestOneLinePrint()
{
	

	for(int i =0; i < 500; ++i)
	{ 
		cout << "\033[s";
		cout << "\033[34The long describing test bdefore printing the actual value\n";
		cout << "\033[35Splitted to a few lines \n";
		cout << i;
		cout << "\033[u";
		std::this_thread::sleep_for(100ms);
	}
}

class A {
public:
	virtual void f1() = 0;// { cout << "\nA::f1";  }
	void f2() { cout << "\nA::f2"; }
};

class B : public A {
public:
	void f1() override { cout << "\nB::f1"; };
	virtual void f2() { cout << "\nB::f2"; }
};

void func(A& a)
{
	a.f1();
	a.f2();

}

bool checkRegexp(string str, string exp)
{
	if (str.empty() && exp.empty())
		return true;

	else if (str.empty() || exp.empty())
		return false;

	string::reverse_iterator rit_str = str.rbegin();
	string::reverse_iterator rit_exp = exp.rbegin();
	string::reverse_iterator lit_str = --str.rend();
	string::reverse_iterator lit_exp = --exp.rend();

	while (rit_str != str.rend() && rit_exp != exp.rend())
	{
		if (*rit_str == *rit_exp)
		{
			++rit_str;
			++rit_exp;
		}

		else if (*rit_exp == '?')
		{
			++rit_exp;

			if (rit_exp == exp.rend())
				return false;
			else
			{
				if (*rit_exp == '?')
					return false;

				if (*rit_str == *rit_exp)
				{
					++rit_str;
					++rit_exp;
				}
				else
					return false;
			}
		}
		else
			return false;
	}

	return true;
}

void testRegExp()
{
	vector<pair<string, string>> cases{ {"123", "123"}, {"13", "1?2?3?" }, { "123", "1?23" },
	{ "23", "1?23" }, { "143", "1?23" }, { "1", "1?" }, { "2", "1?" },{ "11", "11?" }};

	for (auto v : cases)
	{
		cout << "\n Case: " << v.first << ", " << v.second << ", test: " 
			<< (checkRegexp(v.first, v.second) ? "True" : "False");
	}

}

} // namespace main2

using namespace nm2;

int main2(int, char**)
{
	TestAlign();
	return 0;
}

