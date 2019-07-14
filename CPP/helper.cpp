#include "stdafx.h"

#include "helper.hpp"

#pragma once

#include <ctime>
#include <cstdint>
#include <vector>
#include <random>
using namespace std;

//----------------------------------------------------------------------------
uint8_t flip_bits(uint8_t x) {
	x = (x >> 4) | (x << 4);
	x = ((x << 2) & 0xcc) | ((x >> 2) & 0x33);
	x = ((x << 1) & 0xaa) | ((x >> 1) & 0x55);
	return x;
}
//----------------------------------------------------------------------------
bool is_littelendian() {
	unsigned short mark = 0x00AB;
	return *(unsigned char*)&mark == 0xAB;
}

//----------------------------------------------------------------------------
int rand_int(int low, int high) {
	static default_random_engine engine{ (unsigned int)time(time_t(0)) };
	uniform_int_distribution<int> dist{ low, high };
	return dist(engine);
}

//----------------------------------------------------------------------------

inline size_t br2num(char br)
{
	switch (br)
	{
	case '(':
	case ')': return 0;
	case '[':
	case ']': return 1;
	case '{':
	case '}': return 2;
	default: return 0xff;
	}
}

bool check_braces(const string& exp)
{
	if (exp.empty())
		return false;

	int br[3];
	::memset(br, 0, sizeof(br));

	string::const_iterator it = exp.begin();
	char exp_ch = 0;

	while (it != exp.end())
	{
		const char ch = *it++;
		const size_t n = br2num(ch);

		if (n == 0xff)
			continue;

		if (ch == '(')
			exp_ch = ')';

		else if (ch == '[')
			exp_ch = ']';

		else if (ch == '{')
			exp_ch = '}';

		else
		{
			if (exp_ch && ch != exp_ch)
				return false;

			exp_ch = 0;

			if (br[n] > 0)
				br[n]--;
			else
				return false;
		}

		if (exp_ch)
			br[n]++;
	}

	return br[0] == 0 && br[1] == 0 && br[2] == 0;
}

//----------------------------------------------------------------------------
void print_perm(string s, string pref)
{
	if (s.size() == 1)
		;// cout << pref << s << endl;
	else
		for (size_t i = 0; i < s.size(); i++)
		{
			string st = s;
			pref.push_back(s[i]);
			s.erase(i, 1);
			print_perm(s, pref);
			pref.pop_back();
			s = st;
		}
}

//----------------------------------------------------------------------------
bool next_perm(string& s)
{
	const size_t size = s.size();

	if (size < 2)
		return false;


	size_t k = size - 2;
	bool res = false;

	do
	{
		if (s[k] < s[k + 1])
		{
			size_t l = size - 1;
			while (k < l)
			{
				if (s[k] < s[l])
				{
					swap(s[k], s[l]);
					reverse(s.begin() + k + 1, s.end());
					break;
				}
				l--;
			}
			res = true;
			break;
		}

	} while (k-- > 0);

	return res;
}

//----------------------------------------------------------------------------
void reverse_str(string& str)
{
	if (str.empty())
		return;

	string::iterator it1 = str.begin();
	string::iterator it2 = --str.end();

	while (it1 < it2)
		swap(*it1++, *it2--);
}

//----------------------------------------------------------------------------
void repl_str(char* str, char ch, const char* rep)
{
	if (str == 0 || ch == 0 || rep == 0)
		return;

	const size_t lrep = strlen(rep);

	size_t nch = 0;
	const char* beg = str;
	while (*str)
	{
		if (*str == ch)
			nch++;
		str++;
	}

	if (nch == 0)
		return;

	char* end = str;
	while (str >= beg && nch)
	{
		if (*str == ch)
		{
			size_t mlen = nch * (lrep - 1);
			::memmove(str + mlen, str, end - str);
			::memcpy(str + mlen - lrep + 1, rep, lrep);
			::memset(str, 0, mlen - lrep + 1);
			end = str;
			nch--;
		}
		str--;
	}

}

//-----------------------------------------------------------------------------
void part(vector<int>& v, int el)
{
	if (v.empty())
		return;

	vector<int>::iterator beg = v.begin();
	vector<int>::iterator end = --v.end();

	while (beg < end)
	{
		while (*beg < el) beg++;
		while (*end > el) end--;

		if (beg < end)
			swap(*beg, *end);
	}
}

