#pragma once

#include <algorithm>
#include <array>
#include <chrono>
#include <fstream>
#include <functional>
#include <future>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <limits>
#include <queue>
#include <map>
#include <memory>
#include <mutex>
#include <random>
#include <regex>
#include <set>
#include <stack>
#include <cstdio>
#include <sstream>
#include <thread>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <typeinfo>

using namespace std;

typedef int util_t;
typedef vector<string> vstrings_t;

struct SLNode {
	util_t val = util_t();
	SLNode* next = nullptr;
};

struct DLNode : public SLNode {
	SLNode* prev = nullptr;
};

struct BTNode {
	util_t val = util_t();
	SLNode* l = nullptr;
	SLNode* r = nullptr;
};

struct GNode {
	bool isVisited = false;
	util_t val = util_t();
	vector<GNode*> gnodes;
};

SLNode* createSLList(const vector<util_t>);
void printSLList(const SLNode*);

template <typename T>
extern void printGrid(const vector<vector<T>>& grid, pair<T, char> subst = pair<T, char>(0, ' '));


vstrings_t SplitString(const string& str);
vstrings_t SplitString(const string& str, const string& delim);

template<typename T>
void printVector(const vector<T>& arr) {
	cout << "[";

	bool first = true;
	for (auto v : arr) {
		cout << (first ? "" : ", ") << v;
		first = false;
	}
	cout << "]";
}
