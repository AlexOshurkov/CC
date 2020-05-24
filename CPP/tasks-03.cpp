#include "stdafx.h"
#pragma hdrstop

using namespace std;

struct mo_t
{
	int i = 0;
	mo_t(int v) : i(v) {}

	void print() const { cout << "\n" << i; }
};

void RemoveChar(string& str, char ch)
{
	if (str.empty())
		return;

	string::iterator it1 = str.begin(); // all cahracters
	string::iterator it2 = str.begin(); // skip ch

	while (it1 != str.end())
	{
		if (*it1 != ch)
		{
			*it2 = *it1;
			++it2;
		}

		++it1;
	}

	str.erase(it2, str.end());
}

void BalancePar(string& str)
{
	if (str.empty())
		return;

	size_t numBr = 0;

//  forward iteration
	for (auto& v : str)
	{
		if (v == '(')
			++numBr;

		if (v == ')')
			if (numBr == 0)
				v = ' ';
			else
				--numBr;
	}

	numBr = 0;

//  reverse iteration
	for (string::reverse_iterator rit = str.rbegin(); rit != str.rend(); ++rit)
	{
		if (*rit == ')')
			++numBr;

		if (*rit == '(')
			if (numBr == 0)
				*rit = ' ';
			else
				--numBr;
	}

	//str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
	RemoveChar(str, ' ');
}


void TestBalancePar()
{
	vector<string> vals{
		"",
		"(",
		")",
		")()(",
		"a(b",
		"a)b",
		"a)b(c)d(e",
		"a(bc)d)e",
		"(()",
		"a((()()(",
		"b)((c))d))",
		"b)))(1)(2) ((c))d))"
	};

	const size_t maxw = std::max_element(vals.begin(), vals.end())->size();

	for (auto& v : vals)
	{
		cout << "\n " << std::setw(maxw) << std::left << v;
		BalancePar(v);
		cout << " --> " << v;
	}
}

void TestRemoveChar()
{
	vector<string> vals = {
		"",
		"aaa",
		"a",
		"bbb",
		"aabaa",
		"ab",
		"ba",
		"babab",
        "abcabcabc"
	};

	const size_t maxw = std::max_element(vals.begin(), vals.end())->size();

	for (auto& v : vals)
	{
		cout << "\n " << std::setw(maxw) << std::left << v;
		RemoveChar(v, 'a');
		cout << " --> " << v;
	}
}

int main3(int, char**)
{
	TestRemoveChar();
	TestBalancePar();
    return 0;
}
