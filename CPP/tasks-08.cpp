#include "stdafx.h"
#pragma hdrstop

using namespace std;

void testPrefixes() {
	cout << "\n--- testPrefixes ---";

	uint64_t n1 = 0b100;
	uint64_t n2 = 0100;
	uint64_t n3 = 0x100;

	cout << "\nn1: " << n1;
	cout << "\nn2: " << n2;
	cout << "\nn3: " << n3;
}

void testChrono() {
	cout << "\n--- testChrono ---";

	auto dv1 = chrono::seconds(1);

	cout << "\n dv1: " << dv1.count() ;

}

template<typename T>
string args_to_str(T x, T y) {
	return string { "(" + std::to_string(x) + ", " + std::to_string(y) + ") = " };
}

typedef string (*func_t)(int x, int y);
typedef function<bool(string)> on_calc_t;

string func_add(int x, int y) {
	return "func_add: " + args_to_str(x, y) + std::to_string(x + y);
}

string func_mul(int x, int y) {
	return "func_mul: " + args_to_str(x, y) + std::to_string(x * y);
}

struct class_calc_t {
	
	struct event_t {
		virtual bool operator()(string sev) = 0;
	};

	on_calc_t _on_calc;
	event_t* _event = nullptr;

	void on_calc(string s) {
		if (_on_calc)
		{
			bool r = _on_calc(s);
			cout << "\n    event handled by cb: " << r;
		}
		if (_event)
		{
			bool r = (*_event)(s);
			cout << "\n    event handled by event_t: " << r;
		}
	}

	string operator()(int x, int y) {
		string s = "class_add_t: " + args_to_str(x, y) + std::to_string(x + y);
		on_calc(s);
		return s;
	}

	string mul(int x, int y) {
		string s = "class_mul: " + args_to_str(x, y) + std::to_string(x * y);
		on_calc(s);
		return s;
	}

	string sub(int x, int y) {
		string s = "class_sub: " + args_to_str(x, y) + std::to_string(x - y);
		on_calc(s);
		return s;
	}
};

struct client_t : class_calc_t::event_t {

	bool calc_event(string sev) {
		cout << "\n    calc_event 1: " + sev;
		return false;
	}

	bool event_t::operator()(string sev) {
		cout << "\n    calc_event 2: " + sev;
		return true;
	}

};

typedef string(class_calc_t::* pclassf_t)(int, int);
typedef function<string(int, int)> event_t;

using namespace std::placeholders;

void testCallback() {
	cout << "\n--- testCallback ---";
	func_t fadd = func_add;
	func_t fmul = func_mul;

	auto evh1 = [](string sev) -> bool { cout << "\n    evh1: " + sev; return true; };

	class_calc_t ccalc;
	client_t client;
	ccalc._on_calc = bind(&client_t::calc_event, client, _1);
	ccalc._event = &client;
	pclassf_t pclassf = &class_calc_t::mul;
	event_t stdfunct = bind(&class_calc_t::sub, ccalc, _1, _2);


	cout << "\n" << fadd(3, 4);
	cout << "\n" << fmul(3, 4);
	cout << "\n" << ccalc(3, 5);
	cout << "\n" << (ccalc.*pclassf)(7, 3);
	cout << "\n" << stdfunct(17, 5);
}

struct phone_t {

	size_t min = 0, max = 0;

	typedef pair<size_t, size_t> npair_t;
	typedef set<npair_t> npairs_t;
	
	npairs_t npairs;

	phone_t(size_t min_, size_t max_) :
		max(max_), min(min_) {

		npairs.insert(npair_t(min, max));
	}

	bool is_available(size_t n) {
		if (n< min || n > max || npairs.empty())
			return false;

		npairs_t::iterator it = npairs.lower_bound(npair_t(n, 0));

		if (it == npairs.end()) {

		} 
		else if (it == npairs.begin()) {

		}
	}
};


void testPhone() {


	
}

void removeChar(string& s, char ch) {

	string::iterator it1 = s.begin();
	string::iterator it2 = it1;

	while (it2 != s.end()) {

		if (it1 == it2 && *it2 != ch) {
			++it1;
			++it2;
			continue;
		}

		if (*it2 != ch) {
			*it1 = *it2;
			++it1;
		}

		++it2;
	}

	s.erase(it1, s.end());
}

void testRemoveChar() {

	cout << "\n >> testRemoveChar <<";
	vector <string> tc {"", "a", "aa", "a1", "1a", "aa123aa4", "12aa34", "a1a", "123"};
	for (auto& v : tc) {
		cout << "\n " << v << " --> ";
		removeChar(v, 'a');
		cout << "\"" << v << "\"";
	}
}
void reorderListNodes2(SLNode*& n) {
	if (!n || !(n->next))
		return;

	SLNode* on = n;
	SLNode* en = n->next;
	SLNode* lon = on;
	SLNode* fen = en;
	
	while (on || en) {

		lon = on;
		if (on && on->next) {
			on->next = on->next->next;
			on = on->next;
		}
		else
			on = nullptr;

		if (en && en->next) {
			en->next = en->next->next;
			en = en->next;
		}
		else
			en = nullptr;
	}

	lon->next = fen;
}

void reorderListNodes(SLNode*& n) {
	char c = 0;
	SLNode* cn  = n;  // curent node
	SLNode* fn[2] = { nullptr, nullptr };
	SLNode* ln[2] = { nullptr, nullptr };

	while (cn != nullptr) {
		
		auto pos = cn->val & 1;
		SLNode* nn = cn->next;
		SLNode* pn = ln[pos]; 

		cn->next = nullptr;

		if (pn == nullptr) {
			fn[pos] = cn;
			ln[pos] = cn;
		}
		else
		{
			pn->next = cn;
			ln[pos] = cn;
		}

		cn = nn;
	}

	if (ln[1])
		ln[1]->next = fn[0];

	n = fn[1];
}

void testListReorder() {
	
	vector<SLNode*> tcases;
	tcases.push_back(createSLList({}));
	tcases.push_back(createSLList({ 1 }));
	tcases.push_back(createSLList({ 1,2 }));
	tcases.push_back(createSLList({ 1, 2, 3 }));
	tcases.push_back(createSLList({ 1, 2, 3, 4}));
	tcases.push_back(createSLList({ 1, 2, 3, 4, 5 }));
	tcases.push_back(createSLList({ 2, 4, 7, 3, 8, 9, 11, 0 }));
	size_t nc = 0;

	for (auto& tc : tcases) {
		cout << "\n\n*** case " << ++nc << " ***";
		cout << "\nsource list: ";
		printSLList(tc);
		reorderListNodes2(tc);
		cout << "\nReordered list: ";
		printSLList(tc);
	}
}


void testSplitString() {
	vstrings_t tcases{ "", "a", "aa bb", "aa    bb    cc" };
	for (const auto& v : tcases) {
		cout << "\n\"" << v << "\" --> ";

		for (const auto& v2 : SplitString(v, " "))
			cout << "\"" << v2 << "\", ";
	}
}

void fillGrid(vector<vector<int>>& grid, size_t x, size_t y, int oldVal, int newVal) {
	
	if (oldVal == newVal)
		return;

	queue<pair<size_t, size_t>> pix;	
	pix.push(pair<size_t, size_t>(x, y));

	while (!pix.empty()) {

		auto cx = pix.front().first;
		auto cy = pix.front().second;

		if (grid[cy][cx] == oldVal) {
			grid[cy][cx] = newVal;

			if (cx > 0)
				pix.push(pair<size_t, size_t>(cx - 1, cy));

			if (cy > 0)
				pix.push(pair<size_t, size_t>(cx, cy - 1));

			if (cx < grid[0].size() - 1)
				pix.push(pair<size_t, size_t>(cx + 1, cy));

			if (cy < grid.size() - 1)
				pix.push(pair<size_t, size_t>(cx, cy + 1));
		}

		pix.pop();
	}
}

// amazon
int getNumIslands(vector<vector<int>> grid) {
	
	if (grid.empty() || grid[0].empty())
		return 0;

	size_t xsize = grid[0].size();
	size_t ysize = grid.size();

	size_t cnt = 0;

	for (size_t cy = 0; cy < ysize; ++cy)
		for (size_t cx = 0; cx < xsize; ++cx) 
			if (grid[cy][cx] == 1) {
				++cnt;
				fillGrid(grid, cx, cy, 1, cnt + 10);
			}

	return cnt;
}

void testIslands() {
	vector<vector<vector<int>>> tcases =
	{
		{
			{{}},
		},
		{
			{{1}},
		},
		{
			{
				{1,1,1},
				{1,1,1},
				{1,1,1}
			},
		},
		{
			{
				{1,0,1},
				{0,1,0},
				{1,0,1}
			},
		},
		{
			{
				{1, 1, 0, 0, 0, 1},
				{0, 0, 1, 0, 0, 1},
				{1, 0, 1, 1, 0, 0},
				{1, 1, 0, 1, 1, 0},
				{0, 1, 0, 0, 1, 1}
			}
		}
	};

	for (auto& v : tcases) {
		cout << "\n -----------";
		printGrid<int>(v);
		cout << "\n Num of islands: " << getNumIslands(v);
	}

}
int main8(int argc, char** argv)
{
	cout << "\n *** main-8 ***";
	//testPrefixes();
	//testChrono();
	//testCallback();
	//testPhone();
	//testRemoveChar();
	//testListReorder();
	//testSplitString();
	//testIslands();

	return 0;
}