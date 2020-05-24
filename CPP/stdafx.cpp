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
