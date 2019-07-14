// cc-5-perm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <cstdint>
#include <vector>
#include <set>
#include <stack>
#include <iostream>
using namespace std;


#include "../helper.hpp"

typedef vector<int> vec_t;
typedef set<vec_t> set_t;
typedef stack<int> stack_t;


void all_perm(set_t& s, const vec_t& v, stack_t st = stack_t()) {

	if (v.empty())
		return;

	if (v.size() > 2)
	{
		for (size_t i = 0; i < v.size(); i++) {
			vec_t v2;

			for (size_t j = 0; j < v.size(); j++)
				if (j == i)
					st.push(v[j]);
				else
					v2.push_back(v[j]);

			all_perm(s, v2, st);
			st.pop();
		}
	}
	else if (v.size() == 2)
	{
		vec_t v3;
		for (; !st.empty();) {
			v3.push_back(st.top());
			st.pop();
		}
		v3.insert(v3.end(), v.begin(), v.end());
		s.insert(v3);
		swap(v3[v3.size() - 1], v3[v3.size() - 2]);
		s.insert(v3);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	vec_t v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	//v1.push_back(0);
	//v1.push_back(6);

	set_t s;
	all_perm(s, v1);

	size_t cnt = 1;
	for (set_t::const_iterator it = s.begin(); it != s.end(); it++)
	{
		const vec_t& v = *it;
		cout << (cnt < 10 ? "  " : " ") << cnt++ << ". ";

		for (size_t i = 0; i < v.size(); i++)
			cout << v[i] << " ";

		cout << endl;
	}
	
	return 0;
}

