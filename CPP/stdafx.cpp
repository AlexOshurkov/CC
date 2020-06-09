// stdafx.cpp : source file that includes just the standard includes
// cc-12.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

SLNode* createSLList(const vector<util_t> vals) {
	SLNode* list = nullptr;
	SLNode* bn = list;

	for (const auto& v : vals) {
		if (list == nullptr) {
			list = new SLNode{ v, nullptr };
			bn = list;
		}
		else {
			list->next = new SLNode{ v, nullptr };
			list = list->next;
		}
	}

	return bn;
}

void printSLList(const SLNode* list) {
	const SLNode* cn = list;
	while (cn) {
		cout << (cn == list ? "" : ", ") << cn->val;
		cn = cn->next;
	}
}

template <typename T>
void printGrid(const vector<vector<T>>& grid, pair<T, char> subst)
{
	cout << "\n";
	for (const auto& r : grid) {
		cout << "\n";
		for (const auto& c : r)
			if (subst.first == c)
				cout << setw(4) << subst.second;
			else
				cout << setw(4) << c;
	}
}

template void printGrid<int>(const vector<vector<int>>&, pair<int, char> );

vstrings_t SplitString(const string& str, const string& delim)
{
	regex rg(delim);
	sregex_token_iterator it(str.begin(), str.end(), rg, -1);
	vector<string> res(it, sregex_token_iterator());
	res.erase(remove(res.begin(), res.end(), ""), res.end());
	return res;
}

