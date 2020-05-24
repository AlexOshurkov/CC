#pragma once

#include <algorithm>
#include <chrono>
#include <fstream>
#include <functional>
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

using namespace std;

struct SLNode {
	int val = 0;
	SLNode* next = nullptr;
};

typedef int util_t;

SLNode* createSLList(const vector<util_t>);
void printSLList(const SLNode*);

// TODO: reference additional headers your program requires here
